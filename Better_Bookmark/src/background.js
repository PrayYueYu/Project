import { detectBrowser, openNativeBookmarkManager } from "./browserDetection.js";
import { getBrowserBookmarks, readManagedIndex } from "./bookmarkSync.js";

async function getBookmarkCounts() {
  const [browserBookmarks, managedIndex] = await Promise.all([
    getBrowserBookmarks(),
    readManagedIndex()
  ]);

  return {
    browserCount: browserBookmarks.length,
    managedCount: Object.keys(managedIndex.items || {}).length
  };
}

chrome.runtime.onMessage.addListener((message, _sender, sendResponse) => {
  if (message?.type === "detect-browser") {
    sendResponse(detectBrowser(message.userAgent));
    return false;
  }

  if (message?.type === "bookmark-counts") {
    getBookmarkCounts()
      .then((result) => sendResponse({ ok: true, result }))
      .catch((error) => sendResponse({ ok: false, error: error.message }));
    return true;
  }

  if (message?.type === "open-native-bookmark-manager") {
    openNativeBookmarkManager(detectBrowser(message.userAgent))
      .then((result) => sendResponse(result))
      .catch((error) => sendResponse({ ok: false, error: error.message }));
    return true;
  }

  return false;
});
