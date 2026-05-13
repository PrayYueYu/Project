import { storageGet, storageSet } from "./api.js";
import { detectBrowser, openNativeBookmarkManager } from "./browserDetection.js";
import {
  addManualBookmark,
  checkBrowserBookmarkUpdates,
  getBrowserBookmarks,
  getManagedBrowserKeys,
  getManagedItems,
  importBrowserBookmarks,
  readManagedIndex,
  removeManagedBookmark,
  reorderManagedBookmarks,
  setManagedBookmarkPinned,
  updateBookmarkContent,
  updateManagedBookmark
} from "./bookmarkSync.js";

const VIEW_SETTINGS_KEY = "betterBookmarkManager.viewSettings.v1";

const state = {
  browser: detectBrowser(),
  browserItems: [],
  managerItems: [],
  managedBrowserKeys: new Set(),
  query: "",
  viewMode: "manager",
  importMode: false,
  selectedBrowserIds: new Set(),
  editingBookmarkId: null,
  compactMode: false,
  sidebarCollapsed: false,
  themeMode: "light",
  manualAddVisible: false,
  browserUpdates: null
};
const dragState = {
  bookmarkId: null,
  pinned: false
};

const faviconQueue = [];
let activeFaviconLoads = 0;
const maxActiveFaviconLoads = 12;
const faviconLoadTimeoutMs = 200;

const elements = {
  browserName: document.querySelector("#browserName"),
  nativeUrl: document.querySelector("#nativeUrl"),
  managerViewButton: document.querySelector("#managerViewButton"),
  browserViewButton: document.querySelector("#browserViewButton"),
  openNativeButton: document.querySelector("#openNativeButton"),
  openNativeButtonLabel: document.querySelector("#openNativeButton span"),
  sidebarToggleButton: document.querySelector("#sidebarToggleButton"),
  viewTitle: document.querySelector("#viewTitle"),
  manualAddButton: document.querySelector("#manualAddButton"),
  importFromBrowserButton: document.querySelector("#importFromBrowserButton"),
  checkBrowserButton: document.querySelector("#checkBrowserButton"),
  selectAllBrowserButton: document.querySelector("#selectAllBrowserButton"),
  clearBrowserSelectionButton: document.querySelector("#clearBrowserSelectionButton"),
  confirmImportButton: document.querySelector("#confirmImportButton"),
  cancelImportButton: document.querySelector("#cancelImportButton"),
  compactModeButton: document.querySelector("#compactModeButton"),
  themeModeButton: document.querySelector("#themeModeButton"),
  searchInput: document.querySelector("#searchInput"),
  syncSummary: document.querySelector("#syncSummary"),
  faviconSummary: document.querySelector("#faviconSummary"),
  browserCountLabel: document.querySelector("#browserCountLabel"),
  browserCount: document.querySelector("#browserCount"),
  managedCountLabel: document.querySelector("#managedCountLabel"),
  managedCount: document.querySelector("#managedCount"),
  addedCountLabel: document.querySelector("#addedCountLabel"),
  addedCount: document.querySelector("#addedCount"),
  manualAddPanel: document.querySelector("#manualAddPanel"),
  addTitleInput: document.querySelector("#addTitleInput"),
  addUrlInput: document.querySelector("#addUrlInput"),
  confirmManualAddButton: document.querySelector("#confirmManualAddButton"),
  cancelManualAddButton: document.querySelector("#cancelManualAddButton"),
  bookmarkList: document.querySelector("#bookmarkList"),
  template: document.querySelector("#bookmarkItemTemplate")
};

init();

async function init() {
  await loadViewSettings();
  renderBrowser();
  renderViewMode();
  bindEvents();
  await refreshAllData();
  renderCurrentView();
}

function bindEvents() {
  elements.managerViewButton.addEventListener("click", async () => {
    await switchView("manager");
  });

  elements.browserViewButton.addEventListener("click", async () => {
    await switchView("browser");
  });

  elements.openNativeButton.addEventListener("click", async () => {
    elements.openNativeButton.disabled = true;
    elements.nativeUrl.textContent = "";
    elements.openNativeButtonLabel.textContent = "正在打开...";

    const result = await openNativeBookmarkManager(state.browser);

    elements.openNativeButton.disabled = false;
    elements.openNativeButtonLabel.textContent = "打开原生浏览器";

    if (!result.ok) {
      elements.nativeUrl.textContent = `浏览器阻止了直接打开，请手动访问：${result.url}`;
    }
  });

  elements.sidebarToggleButton.addEventListener("click", async () => {
    state.sidebarCollapsed = !state.sidebarCollapsed;
    renderViewMode();
    await saveViewSettings();
  });

  elements.compactModeButton.addEventListener("click", async () => {
    state.compactMode = !state.compactMode;
    renderViewMode();
    await saveViewSettings();
  });

  elements.themeModeButton.addEventListener("click", async () => {
    state.themeMode = state.themeMode === "dark" ? "light" : "dark";
    renderViewMode();
    await saveViewSettings();
  });

  elements.searchInput.addEventListener("input", (event) => {
    state.query = event.target.value.trim().toLowerCase();
    renderBookmarks();
  });

  elements.manualAddButton.addEventListener("click", () => {
    state.manualAddVisible = true;
    renderCurrentView();
    elements.addTitleInput.focus();
  });

  elements.cancelManualAddButton.addEventListener("click", () => {
    resetManualAddPanel();
    renderCurrentView();
  });

  elements.confirmManualAddButton.addEventListener("click", addManualItem);

  elements.importFromBrowserButton.addEventListener("click", async () => {
    state.importMode = true;
    state.selectedBrowserIds.clear();
    await switchView("browser", { keepImportMode: true });
  });

  elements.checkBrowserButton.addEventListener("click", checkBrowserUpdates);
  elements.selectAllBrowserButton.addEventListener("click", selectAllImportableBrowserItems);
  elements.clearBrowserSelectionButton.addEventListener("click", () => {
    state.selectedBrowserIds.clear();
    renderCurrentView();
  });
  elements.confirmImportButton.addEventListener("click", importSelectedBrowserItems);
  elements.cancelImportButton.addEventListener("click", () => {
    state.importMode = false;
    state.selectedBrowserIds.clear();
    renderCurrentView();
  });
}

async function loadViewSettings() {
  const stored = await storageGet({
    [VIEW_SETTINGS_KEY]: {
      compactMode: false,
      sidebarCollapsed: false,
      themeMode: "light",
      viewMode: "manager"
    }
  });
  const settings = stored[VIEW_SETTINGS_KEY] || {};

  state.compactMode = Boolean(settings.compactMode);
  state.sidebarCollapsed = Boolean(settings.sidebarCollapsed);
  state.themeMode = settings.themeMode === "dark" ? "dark" : "light";
  state.viewMode = settings.viewMode === "browser" ? "browser" : "manager";
}

async function saveViewSettings() {
  await storageSet({
    [VIEW_SETTINGS_KEY]: {
      compactMode: state.compactMode,
      sidebarCollapsed: state.sidebarCollapsed,
      themeMode: state.themeMode,
      viewMode: state.viewMode
    }
  });
}

async function refreshAllData() {
  await Promise.all([refreshManagerData(), refreshBrowserData()]);
}

async function refreshManagerData() {
  const index = await readManagedIndex();
  state.managerItems = getManagedItems(index);
  state.managedBrowserKeys = getManagedBrowserKeys(index);
}

async function refreshBrowserData() {
  state.browserItems = await getBrowserBookmarks();
}

async function switchView(viewMode, options = {}) {
  state.viewMode = viewMode;
  state.editingBookmarkId = null;
  state.manualAddVisible = false;

  if (!options.keepImportMode) {
    state.importMode = false;
    state.selectedBrowserIds.clear();
  }

  if (viewMode === "browser") {
    await refreshBrowserData();
  } else {
    await refreshManagerData();
  }

  await saveViewSettings();
  renderCurrentView();
}

function renderViewMode() {
  document.body.classList.toggle("is-compact-mode", state.compactMode);
  document.body.classList.toggle("is-sidebar-collapsed", state.sidebarCollapsed);
  document.body.classList.toggle("is-dark-mode", state.themeMode === "dark");
  document.body.classList.toggle("is-browser-view", state.viewMode === "browser");
  document.body.classList.toggle("is-manager-view", state.viewMode === "manager");
  document.body.classList.toggle("is-import-mode", state.importMode);

  elements.compactModeButton.setAttribute("aria-pressed", String(state.compactMode));
  elements.compactModeButton.textContent = state.compactMode ? "完整模式" : "极简模式";
  elements.themeModeButton.setAttribute("aria-pressed", String(state.themeMode === "dark"));
  elements.themeModeButton.textContent = state.themeMode === "dark" ? "亮色模式" : "暗色模式";
  elements.sidebarToggleButton.setAttribute("aria-pressed", String(state.sidebarCollapsed));
  elements.sidebarToggleButton.setAttribute(
    "aria-label",
    state.sidebarCollapsed ? "展开左侧菜单栏" : "收起左侧菜单栏"
  );
  elements.sidebarToggleButton.textContent = state.sidebarCollapsed ? ">" : "<";
  elements.managerViewButton.setAttribute("aria-pressed", String(state.viewMode === "manager"));
  elements.browserViewButton.setAttribute("aria-pressed", String(state.viewMode === "browser"));
}

function renderBrowser() {
  elements.browserName.textContent = state.browser.name;
  elements.nativeUrl.textContent = "";
}

function renderCurrentView() {
  renderViewMode();
  renderToolbar();
  renderStats();
  renderBookmarks();
}

function renderToolbar() {
  const isManager = state.viewMode === "manager";
  const isBrowser = state.viewMode === "browser";
  const isImporting = isBrowser && state.importMode;

  elements.viewTitle.textContent = isManager ? "管理器书签" : "浏览器书签";
  elements.manualAddButton.hidden = !isManager;
  elements.importFromBrowserButton.hidden = !isManager;
  elements.checkBrowserButton.hidden = !isBrowser || isImporting;
  elements.selectAllBrowserButton.hidden = !isImporting;
  elements.clearBrowserSelectionButton.hidden = !isImporting;
  elements.confirmImportButton.hidden = !isImporting;
  elements.cancelImportButton.hidden = !isImporting;
  elements.manualAddPanel.hidden = !state.manualAddVisible || !isManager;

  if (isManager) {
    elements.syncSummary.textContent = "管理器书签独立保存在插件中，可手动添加，也可从浏览器书签中选择导入。";
  } else if (isImporting) {
    elements.syncSummary.textContent = `选择要加入管理器的浏览器书签。已选择 ${state.selectedBrowserIds.size} 个，已存在的会自动跳过。`;
  } else {
    elements.syncSummary.textContent = "浏览器书签为只读模式。可手动检查浏览器中新增或已删除的书签。";
  }
}

function renderStats() {
  elements.browserCountLabel.textContent = "浏览器书签";
  elements.browserCount.textContent = String(state.browserItems.length);
  elements.managedCountLabel.textContent = "管理器书签";
  elements.managedCount.textContent = String(state.managerItems.length);

  if (state.viewMode === "browser" && state.browserUpdates) {
    elements.addedCountLabel.textContent = "新增/删除";
    elements.addedCount.textContent = `${state.browserUpdates.added.length}/${state.browserUpdates.deleted.length}`;
    return;
  }

  if (state.viewMode === "browser" && state.importMode) {
    elements.addedCountLabel.textContent = "已选择";
    elements.addedCount.textContent = String(state.selectedBrowserIds.size);
    return;
  }

  elements.addedCountLabel.textContent = "当前视图";
  elements.addedCount.textContent = String(getVisibleItems().length);
}

function renderBookmarks() {
  const fragment = document.createDocumentFragment();
  const items = getVisibleItems();
  const renderToken = crypto.randomUUID();

  state.renderToken = renderToken;
  state.faviconStats = {
    total: items.length,
    done: 0,
    ok: 0,
    failed: 0
  };
  renderFaviconSummary();
  elements.bookmarkList.replaceChildren();

  if (!items.length) {
    const empty = document.createElement("p");
    empty.className = "empty-state";
    empty.textContent = state.query ? "没有匹配的书签。" : "当前视图还没有书签。";
    elements.bookmarkList.append(empty);
    renderFaviconSummary();
    return;
  }

  if (state.viewMode === "browser") {
    fragment.append(renderBookmarkSection("浏览器书签", items, false, renderToken));
  } else {
    const pinnedItems = items.filter((item) => item.pinned);
    const regularItems = items.filter((item) => !item.pinned);

    if (pinnedItems.length) {
      fragment.append(renderBookmarkSection("置顶", pinnedItems, true, renderToken));
    }

    if (regularItems.length) {
      fragment.append(
        renderBookmarkSection(pinnedItems.length ? "其他书签" : "管理器书签", regularItems, false, renderToken)
      );
    }
  }

  elements.bookmarkList.append(fragment);
}

function renderBookmarkSection(title, items, pinned, renderToken) {
  const section = document.createElement("section");
  const header = document.createElement("div");
  const heading = document.createElement("h3");
  const count = document.createElement("span");
  const list = document.createElement("div");
  const canReorder = state.viewMode === "manager";

  section.className = "bookmark-section";
  section.dataset.pinnedSection = String(pinned);
  header.className = "bookmark-section-header";
  heading.textContent = title;
  count.textContent = `${items.length}`;
  list.className = "bookmark-section-list";
  list.dataset.pinnedGroup = String(pinned);

  if (canReorder) {
    list.addEventListener("dragover", (event) => handleDragOver(event, list, pinned));
    list.addEventListener("drop", (event) => handleDrop(event, list, pinned));
    list.addEventListener("dragleave", (event) => {
      if (!list.contains(event.relatedTarget)) {
        list.classList.remove("is-drag-over");
      }
    });
  }

  for (const item of items) {
    list.append(createBookmarkNode(item, renderToken));
  }

  header.append(heading, count);
  section.append(header, list);

  return section;
}

function createBookmarkNode(item, renderToken) {
  const isManager = state.viewMode === "manager";
  const isBrowser = state.viewMode === "browser";
  const isEditing = isManager && state.editingBookmarkId === item.bookmarkId;
  const isImported = isBrowser && isBrowserBookmarkImported(item);
  const node = elements.template.content.firstElementChild.cloneNode(true);
  const dragHandle = node.querySelector(".drag-handle");
  const select = node.querySelector(".bookmark-select");
  const checkbox = node.querySelector(".browser-select-checkbox");
  const favicon = node.querySelector(".favicon");
  const title = node.querySelector(".bookmark-title");
  const titleInput = node.querySelector(".title-edit-input");
  const url = node.querySelector(".bookmark-url");
  const urlInput = node.querySelector(".url-edit-input");
  const status = node.querySelector(".status-pill");
  const dateAdded = node.querySelector(".date-added");
  const tagInput = node.querySelector(".tag-input");
  const noteInput = node.querySelector(".note-input");
  const editorRow = node.querySelector(".editor-row");
  const actions = node.querySelector(".bookmark-actions");
  const editButton = node.querySelector(".edit-button");
  const pinButton = node.querySelector(".pin-button");
  const deleteButton = node.querySelector(".delete-button");

  node.classList.toggle("is-readonly", isBrowser);
  node.classList.toggle("is-editing", isEditing);
  node.classList.toggle("is-imported", isImported);
  node.draggable = false;
  node.dataset.bookmarkId = item.bookmarkId;
  node.dataset.pinned = String(Boolean(item.pinned));
  dragHandle.hidden = !isManager || isEditing;
  dragHandle.draggable = isManager && !isEditing;

  if (isManager && !isEditing) {
    dragHandle.addEventListener("dragstart", (event) => handleDragStart(event, item));
    node.addEventListener("dragend", handleDragEnd);
  }

  title.href = item.url;
  title.textContent = item.title || item.url;
  title.setAttribute("aria-label", `打开 ${item.title || item.url}`);
  titleInput.value = item.title || "";
  url.textContent = item.url;
  urlInput.value = item.url || "";
  renderFavicon(favicon, item, renderToken);
  status.textContent = getStatusLabel(item, { isBrowser, isImported });
  dateAdded.textContent = formatDate(item.dateAdded || item.createdAt);
  tagInput.value = (item.tags || []).join(", ");
  noteInput.value = item.note || "";

  select.hidden = !isBrowser || !state.importMode;
  checkbox.checked = state.selectedBrowserIds.has(item.bookmarkId);
  checkbox.disabled = isImported;
  checkbox.addEventListener("change", () => {
    if (checkbox.checked) {
      state.selectedBrowserIds.add(item.bookmarkId);
    } else {
      state.selectedBrowserIds.delete(item.bookmarkId);
    }
    renderToolbar();
    renderStats();
  });

  editorRow.hidden = !isManager;
  actions.hidden = !isManager;
  tagInput.disabled = !isManager;
  noteInput.disabled = !isManager;
  title.hidden = isEditing;
  url.hidden = isEditing;
  titleInput.hidden = !isEditing;
  urlInput.hidden = !isEditing;
  editButton.textContent = isEditing ? "确认" : "编辑";
  pinButton.textContent = item.pinned ? "取消置顶" : "置顶";
  pinButton.setAttribute("aria-pressed", String(Boolean(item.pinned)));

  tagInput.addEventListener("change", async () => {
    const tags = tagInput.value
      .split(",")
      .map((tag) => tag.trim())
      .filter(Boolean);
    await updateItem(item.bookmarkId, { tags });
  });

  noteInput.addEventListener("change", async () => {
    await updateItem(item.bookmarkId, { note: noteInput.value.trim() });
  });

  editButton.addEventListener("click", async (event) => {
    event.stopPropagation();

    if (isEditing) {
      await confirmInlineEdit(item, titleInput.value, urlInput.value);
      return;
    }

    state.editingBookmarkId = item.bookmarkId;
    renderBookmarks();
  });

  pinButton.addEventListener("click", async (event) => {
    event.stopPropagation();
    await togglePinned(item);
  });

  deleteButton.addEventListener("click", async (event) => {
    event.stopPropagation();
    await deleteItem(item);
  });

  return node;
}

function getVisibleItems() {
  const sourceItems = state.viewMode === "browser" ? state.browserItems : state.managerItems;

  return sourceItems.filter((item) => {
    if (!state.query) {
      return true;
    }

    const haystack = [
      item.title,
      item.url,
      item.note,
      ...(item.tags || [])
    ]
      .filter(Boolean)
      .join(" ")
      .toLowerCase();

    return haystack.includes(state.query);
  });
}

async function addManualItem() {
  const title = elements.addTitleInput.value.trim();
  const url = normalizeBookmarkUrl(elements.addUrlInput.value);

  if (!title) {
    elements.syncSummary.textContent = "书签名称不能为空。";
    elements.addTitleInput.focus();
    return;
  }

  if (!url) {
    elements.syncSummary.textContent = "请输入有效的 http:// 或 https:// 网址。";
    elements.addUrlInput.focus();
    return;
  }

  const result = await addManualBookmark({ title, url });
  state.managerItems = getManagedItems(result.index);
  state.managedBrowserKeys = getManagedBrowserKeys(result.index);
  resetManualAddPanel();
  elements.syncSummary.textContent = `已添加到管理器：${title}`;
  renderCurrentView();
}

function resetManualAddPanel() {
  state.manualAddVisible = false;
  elements.addTitleInput.value = "";
  elements.addUrlInput.value = "";
}

async function checkBrowserUpdates() {
  elements.checkBrowserButton.disabled = true;
  elements.syncSummary.textContent = "正在检查浏览器书签变化...";

  try {
    const result = await checkBrowserBookmarkUpdates();
    state.browserItems = result.current;
    state.browserUpdates = {
      added: result.added,
      deleted: result.deleted
    };
    elements.syncSummary.textContent = `检查完成：新增 ${result.added.length} 个，删除 ${result.deleted.length} 个。`;
    renderCurrentView();
  } catch (error) {
    elements.syncSummary.textContent = `检查失败：${error.message || error}`;
  } finally {
    elements.checkBrowserButton.disabled = false;
  }
}

function selectAllImportableBrowserItems() {
  for (const item of getVisibleItems()) {
    if (!isBrowserBookmarkImported(item)) {
      state.selectedBrowserIds.add(item.bookmarkId);
    }
  }

  renderCurrentView();
}

async function importSelectedBrowserItems() {
  const selected = state.browserItems.filter((item) => state.selectedBrowserIds.has(item.bookmarkId));

  if (!selected.length) {
    elements.syncSummary.textContent = "请先勾选要加入管理器的浏览器书签。";
    return;
  }

  const result = await importBrowserBookmarks(selected);
  state.managerItems = getManagedItems(result.index);
  state.managedBrowserKeys = getManagedBrowserKeys(result.index);
  state.selectedBrowserIds.clear();
  state.importMode = false;
  state.viewMode = "manager";
  elements.syncSummary.textContent = `已加入 ${result.imported.length} 个，跳过已存在 ${result.skipped.length} 个。`;
  await saveViewSettings();
  renderCurrentView();
}

async function updateItem(bookmarkId, patch) {
  const updated = await updateManagedBookmark(bookmarkId, patch);
  state.managerItems = state.managerItems.map((item) =>
    item.bookmarkId === bookmarkId ? updated : item
  );
  renderBookmarks();
}

async function togglePinned(item) {
  const nextPinned = !item.pinned;
  const result = await setManagedBookmarkPinned(item.bookmarkId, nextPinned);

  state.managerItems = getManagedItems(result.index);
  elements.syncSummary.textContent = nextPinned
    ? `已置顶：${item.title || item.url}`
    : `已取消置顶：${item.title || item.url}`;
  renderCurrentView();
}

async function confirmInlineEdit(item, titleValue, urlValue) {
  const title = titleValue.trim();
  const url = normalizeBookmarkUrl(urlValue);

  if (!title) {
    elements.syncSummary.textContent = "书签名称不能为空。";
    return;
  }

  if (!url) {
    elements.syncSummary.textContent = "请输入有效的 http:// 或 https:// 网址。";
    return;
  }

  const result = await updateBookmarkContent(item.bookmarkId, { title, url });
  state.managerItems = getManagedItems(result.index);
  state.managedBrowserKeys = getManagedBrowserKeys(result.index);
  state.editingBookmarkId = null;
  elements.syncSummary.textContent = `已更新：${title}`;
  renderCurrentView();
}

async function deleteItem(item) {
  const title = item.title || item.url;
  const confirmed = confirm(`确定要从管理器中移除这个书签吗？\n\n${title}`);

  if (!confirmed) {
    return;
  }

  const result = await removeManagedBookmark(item.bookmarkId);

  state.managerItems = getManagedItems(result.index);
  state.managedBrowserKeys = getManagedBrowserKeys(result.index);
  elements.syncSummary.textContent = `已从管理器移除：${title}`;
  renderCurrentView();
}

function isBrowserBookmarkImported(item) {
  return (
    state.managedBrowserKeys.has(`id:${item.bookmarkId}`) ||
    state.managedBrowserKeys.has(`url:${normalizeUrlKey(item.url)}`)
  );
}

function normalizeBookmarkUrl(value) {
  const trimmed = value.trim();

  if (!trimmed) {
    return null;
  }

  try {
    const url = new URL(trimmed);

    if (url.protocol !== "http:" && url.protocol !== "https:") {
      return null;
    }

    return url.toString();
  } catch {
    return null;
  }
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

function handleDragStart(event, item) {
  const node = event.currentTarget.closest(".bookmark-item");

  if (state.viewMode !== "manager" || !node) {
    event.preventDefault();
    return;
  }

  event.stopPropagation();
  dragState.bookmarkId = item.bookmarkId;
  dragState.pinned = Boolean(item.pinned);
  event.dataTransfer.effectAllowed = "move";
  event.dataTransfer.setData("text/plain", item.bookmarkId);
  event.dataTransfer.setDragImage(node, 24, 24);

  requestAnimationFrame(() => {
    node.classList.add("is-dragging");
  });
}

function handleDragOver(event, list, pinned) {
  if (!dragState.bookmarkId || dragState.pinned !== pinned) {
    if (event.dataTransfer) {
      event.dataTransfer.dropEffect = "none";
    }
    return;
  }

  event.preventDefault();
  list.classList.add("is-drag-over");

  const dragging = document.querySelector(".bookmark-item.is-dragging");

  if (!dragging) {
    return;
  }

  const afterElement = getDragAfterElement(list, event.clientY);

  if (!afterElement) {
    list.append(dragging);
  } else {
    list.insertBefore(dragging, afterElement);
  }
}

async function handleDrop(event, list, pinned) {
  list.classList.remove("is-drag-over");

  if (!dragState.bookmarkId || dragState.pinned !== pinned) {
    return;
  }

  event.preventDefault();

  const orderedIds = [...list.querySelectorAll(".bookmark-item")]
    .map((item) => item.dataset.bookmarkId)
    .filter(Boolean);
  const result = await reorderManagedBookmarks(orderedIds, pinned);

  state.managerItems = getManagedItems(result.index);
  elements.syncSummary.textContent = pinned ? "已更新置顶区域顺序。" : "已更新普通区域顺序。";
  renderCurrentView();
}

function handleDragEnd() {
  dragState.bookmarkId = null;
  dragState.pinned = false;
  document.querySelectorAll(".bookmark-item.is-dragging").forEach((item) => {
    item.classList.remove("is-dragging");
  });
  document.querySelectorAll(".bookmark-section-list.is-drag-over").forEach((list) => {
    list.classList.remove("is-drag-over");
  });
}

function getDragAfterElement(container, y) {
  const draggableElements = [
    ...container.querySelectorAll(".bookmark-item:not(.is-dragging)")
  ];

  return draggableElements.reduce(
    (closest, child) => {
      const box = child.getBoundingClientRect();
      const offset = y - box.top - box.height / 2;

      if (offset < 0 && offset > closest.offset) {
        return {
          offset,
          element: child
        };
      }

      return closest;
    },
    {
      offset: Number.NEGATIVE_INFINITY,
      element: null
    }
  ).element;
}

function getStatusLabel(item, { isBrowser, isImported }) {
  if (isBrowser) {
    return isImported ? "已加入管理器" : "浏览器只读";
  }

  if (item.pinned) {
    return "置顶";
  }

  if (item.source === "manual") {
    return "手动添加";
  }

  if (item.source === "browser-import") {
    return "浏览器导入";
  }

  return "管理器";
}

function formatDate(dateAdded) {
  if (!dateAdded) {
    return "无收藏时间";
  }

  return new Intl.DateTimeFormat("zh-CN", {
    year: "numeric",
    month: "2-digit",
    day: "2-digit"
  }).format(new Date(dateAdded));
}

async function renderFavicon(container, item, renderToken) {
  container.classList.remove("has-image");
  container.textContent = getFallbackInitial(item);
  container.title = "使用 Google favicon";
  const token = crypto.randomUUID();
  container.dataset.faviconToken = token;

  const result = await enqueueFaviconLoad(async () => {
    return resolveFaviconFromGoogle(item.url);
  });

  if (container.dataset.faviconToken !== token) {
    return;
  }

  const img = result.image;
  img.alt = "";
  img.title = "";
  let finished = false;
  const fallbackToInitial = (reason) => {
    if (finished || container.dataset.faviconToken !== token) {
      return;
    }

    finished = true;
    container.classList.remove("has-image");
    container.textContent = getFallbackInitial(item);
    container.title = reason;
    updateFaviconStats(renderToken, false);
  };
  const timeoutId = setTimeout(() => {
    fallbackToInitial(`favicon.im 图片超过 ${faviconLoadTimeoutMs}ms 未加载：${result.sourceUrl}`);
  }, faviconLoadTimeoutMs);

  img.addEventListener(
    "error",
    () => {
      clearTimeout(timeoutId);
      fallbackToInitial(`favicon.im 图片加载失败：${result.sourceUrl}`);
    },
    { once: true }
  );
  img.addEventListener(
    "load",
    () => {
      if (finished || container.dataset.faviconToken !== token) {
        return;
      }

      finished = true;
      clearTimeout(timeoutId);
      updateFaviconStats(renderToken, true);
    },
    { once: true }
  );
  container.textContent = "";
  container.append(img);
  container.classList.add("has-image");
  container.title = result.sourceUrl;
}

async function resolveFaviconFromGoogle(pageUrl) {
  let page;

  try {
    page = new URL(pageUrl);
  } catch {
    page = null;
  }

  const domain = page?.hostname || pageUrl;
  const sourceUrl = getGoogleFaviconUrl(domain);
  const image = new Image();

  image.decoding = "async";
  image.referrerPolicy = "no-referrer";
  image.src = sourceUrl;

  return {
    ok: true,
    image,
    iconUrl: sourceUrl,
    sourceUrl: `Google S2: ${sourceUrl}`
  };
}

function getGoogleFaviconUrl(domain) {
  return `https://favicon.im/zh/${encodeURIComponent(domain)}`;
}

function enqueueFaviconLoad(task) {
  return new Promise((resolve) => {
    faviconQueue.push({ task, resolve });
    runNextFaviconLoad();
  });
}

function runNextFaviconLoad() {
  while (activeFaviconLoads < maxActiveFaviconLoads && faviconQueue.length) {
    const job = faviconQueue.shift();
    activeFaviconLoads += 1;

    Promise.resolve()
      .then(job.task)
      .then(job.resolve)
      .catch((error) => {
        job.resolve({
          ok: false,
          error: error.message || String(error)
        });
      })
      .finally(() => {
        activeFaviconLoads -= 1;
        runNextFaviconLoad();
      });
  }
}

function getFallbackInitial(item) {
  try {
    const hostname = new URL(item.url).hostname.replace(/^www\./, "");
    return hostname[0]?.toUpperCase() || "?";
  } catch {
    return (item.title || "?")[0]?.toUpperCase() || "?";
  }
}

function updateFaviconStats(renderToken, ok) {
  if (state.renderToken !== renderToken || !state.faviconStats) {
    return;
  }

  state.faviconStats.done += 1;

  if (ok) {
    state.faviconStats.ok += 1;
  } else {
    state.faviconStats.failed += 1;
  }

  renderFaviconSummary();
}

function renderFaviconSummary() {
  if (!elements.faviconSummary || !state.faviconStats) {
    return;
  }

  const { total, done, ok, failed } = state.faviconStats;

  if (!total) {
    elements.faviconSummary.textContent = "站点图标：没有需要加载的书签。";
    return;
  }

  elements.faviconSummary.textContent = `站点图标：${done}/${total}，成功 ${ok}，失败 ${failed}`;
}
