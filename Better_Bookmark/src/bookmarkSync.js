import { callChromeApi, getBookmarksApi, storageGet, storageSet } from "./api.js";

export const BOOKMARK_INDEX_KEY = "betterBookmarkManager.index.v1";
export const BROWSER_SNAPSHOT_KEY = "betterBookmarkManager.browserSnapshot.v1";

export async function getBrowserBookmarks() {
  const bookmarks = getBookmarksApi();
  const tree = await callChromeApi(bookmarks.getTree, bookmarks);

  return flattenBookmarkTree(tree);
}

export function flattenBookmarkTree(nodes, parentId = null, output = []) {
  for (const node of nodes || []) {
    const currentParentId = node.parentId || parentId;

    if (node.url) {
      output.push({
        bookmarkId: node.id,
        title: node.title || node.url,
        url: node.url,
        parentId: currentParentId,
        dateAdded: node.dateAdded || null,
        source: "browser"
      });
    }

    if (node.children?.length) {
      flattenBookmarkTree(node.children, node.id, output);
    }
  }

  return output;
}

export async function readManagedIndex() {
  const stored = await storageGet({
    [BOOKMARK_INDEX_KEY]: {
      version: 2,
      items: {}
    }
  });
  const index = stored[BOOKMARK_INDEX_KEY] || { version: 2, items: {} };

  return {
    version: 2,
    items: normalizeManagedItems(index.items || {})
  };
}

export async function writeManagedIndex(index) {
  await storageSet({
    [BOOKMARK_INDEX_KEY]: {
      version: 2,
      items: index.items || {}
    }
  });
}

export async function addManualBookmark(patch) {
  const index = await readManagedIndex();
  const now = Date.now();
  const bookmarkId = `manual:${crypto.randomUUID()}`;
  const bookmark = createManagedBookmark({
    bookmarkId,
    title: patch.title,
    url: patch.url,
    source: "manual",
    now,
    sortOrder: getNextSortOrder(index, false)
  });

  index.items[bookmarkId] = bookmark;
  await writeManagedIndex(index);

  return {
    bookmark,
    index
  };
}

export async function importBrowserBookmarks(browserBookmarks) {
  const index = await readManagedIndex();
  const now = Date.now();
  const imported = [];
  const skipped = [];

  for (const browserBookmark of browserBookmarks) {
    const existing = findExistingManagedBookmark(index, browserBookmark);

    if (existing) {
      skipped.push(existing);
      continue;
    }

    const bookmarkId = `browser:${browserBookmark.bookmarkId}`;
    const bookmark = createManagedBookmark({
      bookmarkId,
      title: browserBookmark.title,
      url: browserBookmark.url,
      source: "browser-import",
      sourceBookmarkId: browserBookmark.bookmarkId,
      parentId: browserBookmark.parentId,
      dateAdded: browserBookmark.dateAdded,
      now,
      sortOrder: getNextSortOrder(index, false)
    });

    index.items[bookmarkId] = bookmark;
    imported.push(bookmark);
  }

  if (imported.length) {
    await writeManagedIndex(index);
  }

  return {
    imported,
    skipped,
    index
  };
}

export async function updateManagedBookmark(bookmarkId, patch) {
  const index = await readManagedIndex();
  const existing = index.items[bookmarkId];

  if (!existing) {
    throw new Error(`Managed bookmark ${bookmarkId} does not exist.`);
  }

  index.items[bookmarkId] = {
    ...existing,
    ...patch,
    bookmarkId,
    updatedAt: Date.now()
  };

  await writeManagedIndex(index);

  return index.items[bookmarkId];
}

export async function updateBookmarkContent(bookmarkId, patch) {
  const index = await readManagedIndex();
  const existing = index.items[bookmarkId];

  if (!existing) {
    throw new Error(`Managed bookmark ${bookmarkId} does not exist.`);
  }

  index.items[bookmarkId] = {
    ...existing,
    title: patch.title?.trim() || existing.title || existing.url,
    url: patch.url?.trim() || existing.url,
    updatedAt: Date.now()
  };

  await writeManagedIndex(index);

  return {
    bookmark: index.items[bookmarkId],
    index
  };
}

export async function setManagedBookmarkPinned(bookmarkId, pinned) {
  const index = await readManagedIndex();
  const existing = index.items[bookmarkId];

  if (!existing) {
    throw new Error(`Managed bookmark ${bookmarkId} does not exist.`);
  }

  index.items[bookmarkId] = {
    ...existing,
    pinned,
    sortOrder: getNextSortOrder(index, pinned),
    updatedAt: Date.now()
  };

  await writeManagedIndex(index);

  return {
    bookmark: index.items[bookmarkId],
    index
  };
}

export async function reorderManagedBookmarks(bookmarkIds, pinned) {
  const index = await readManagedIndex();
  const now = Date.now();

  bookmarkIds.forEach((bookmarkId, sortOrder) => {
    const existing = index.items[bookmarkId];

    if (!existing || Boolean(existing.pinned) !== pinned) {
      return;
    }

    index.items[bookmarkId] = {
      ...existing,
      sortOrder,
      updatedAt: now
    };
  });

  await writeManagedIndex(index);

  return {
    index
  };
}

export async function removeManagedBookmark(bookmarkId) {
  const index = await readManagedIndex();
  const managedDeleted = Boolean(index.items[bookmarkId]);

  delete index.items[bookmarkId];
  await writeManagedIndex(index);

  return {
    bookmarkId,
    managedDeleted,
    index
  };
}

export function getManagedItems(index) {
  return Object.values(index.items || {}).sort((a, b) => {
    if (Boolean(a.pinned) !== Boolean(b.pinned)) {
      return a.pinned ? -1 : 1;
    }

    return getSortOrder(a) - getSortOrder(b);
  });
}

export function getManagedBrowserKeys(index) {
  const keys = new Set();

  for (const item of Object.values(index.items || {})) {
    if (item.sourceBookmarkId) {
      keys.add(`id:${item.sourceBookmarkId}`);
    }

    if (item.url) {
      keys.add(`url:${normalizeUrlKey(item.url)}`);
    }
  }

  return keys;
}

export async function checkBrowserBookmarkUpdates() {
  const current = await getBrowserBookmarks();
  const previous = await readBrowserSnapshot();
  const previousById = new Map(previous.map((item) => [item.bookmarkId, item]));
  const currentById = new Map(current.map((item) => [item.bookmarkId, item]));
  const added = current.filter((item) => !previousById.has(item.bookmarkId));
  const deleted = previous.filter((item) => !currentById.has(item.bookmarkId));

  await writeBrowserSnapshot(current);

  return {
    current,
    added,
    deleted,
    browserCount: current.length
  };
}

export async function readBrowserSnapshot() {
  const stored = await storageGet({
    [BROWSER_SNAPSHOT_KEY]: []
  });

  return Array.isArray(stored[BROWSER_SNAPSHOT_KEY])
    ? stored[BROWSER_SNAPSHOT_KEY]
    : [];
}

export async function writeBrowserSnapshot(items) {
  await storageSet({
    [BROWSER_SNAPSHOT_KEY]: items.map((item) => ({
      bookmarkId: item.bookmarkId,
      title: item.title,
      url: item.url,
      parentId: item.parentId,
      dateAdded: item.dateAdded || null
    }))
  });
}

function createManagedBookmark({
  bookmarkId,
  title,
  url,
  source,
  sourceBookmarkId = null,
  parentId = null,
  dateAdded = null,
  now,
  sortOrder
}) {
  return {
    bookmarkId,
    title: title?.trim() || url,
    url: url.trim(),
    parentId,
    dateAdded,
    tags: [],
    note: "",
    status: "manager",
    pinned: false,
    sortOrder,
    source,
    sourceBookmarkId,
    createdAt: now,
    updatedAt: now
  };
}

function normalizeManagedItems(items) {
  const normalized = {};
  const now = Date.now();

  for (const [key, item] of Object.entries(items)) {
    const bookmarkId = item.bookmarkId || key;

    normalized[bookmarkId] = {
      ...item,
      bookmarkId,
      title: item.title || item.url || "未命名书签",
      url: item.url || "",
      tags: Array.isArray(item.tags) ? item.tags : [],
      note: item.note || "",
      status: item.status || "manager",
      pinned: Boolean(item.pinned),
      source: item.source || "manager",
      sourceBookmarkId: item.sourceBookmarkId || null,
      sortOrder:
        typeof item.sortOrder === "number"
          ? item.sortOrder
          : getFallbackSortOrder(item),
      createdAt: item.createdAt || now,
      updatedAt: item.updatedAt || now
    };
  }

  return normalized;
}

function findExistingManagedBookmark(index, browserBookmark) {
  const normalizedUrl = normalizeUrlKey(browserBookmark.url);

  return Object.values(index.items || {}).find((item) => {
    return (
      item.sourceBookmarkId === browserBookmark.bookmarkId ||
      item.bookmarkId === browserBookmark.bookmarkId ||
      item.bookmarkId === `browser:${browserBookmark.bookmarkId}` ||
      normalizeUrlKey(item.url) === normalizedUrl
    );
  });
}

function normalizeUrlKey(url) {
  try {
    const parsed = new URL(url);
    parsed.hash = "";
    return parsed.toString();
  } catch {
    return String(url || "").trim();
  }
}

function getNextSortOrder(index, pinned) {
  const groupItems = Object.values(index.items || {}).filter((item) => {
    return Boolean(item.pinned) === pinned;
  });
  const maxOrder = groupItems.reduce((max, item) => {
    return Math.max(max, getSortOrder(item));
  }, -1);

  return maxOrder + 1;
}

function getSortOrder(item) {
  return typeof item.sortOrder === "number"
    ? item.sortOrder
    : getFallbackSortOrder(item);
}

function getFallbackSortOrder(item) {
  return 1_000_000_000_000_000 - (item.dateAdded || item.createdAt || 0);
}
