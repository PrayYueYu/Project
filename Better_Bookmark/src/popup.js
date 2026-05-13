import { detectBrowser, openNativeBookmarkManager } from "./browserDetection.js";
import { getBrowserBookmarks, readManagedIndex } from "./bookmarkSync.js";

const browser = detectBrowser();
const browserLine = document.querySelector("#popupBrowser");
const syncStatus = document.querySelector("#popupSyncStatus");
const openManagerButton = document.querySelector("#popupOpenManager");
const openNativeButton = document.querySelector("#popupOpenNative");

browserLine.textContent = `当前浏览器：${browser.name}`;

openManagerButton.addEventListener("click", () => {
  chrome.runtime.openOptionsPage();
});

openNativeButton.addEventListener("click", async () => {
  openNativeButton.disabled = true;
  openNativeButton.textContent = "正在打开...";

  const result = await openNativeBookmarkManager(browser);

  if (!result.ok) {
    syncStatus.textContent = `请手动访问：${result.url}`;
  }

  openNativeButton.disabled = false;
  openNativeButton.textContent = "打开原生书签页";
});

loadCounts();

async function loadCounts() {
  try {
    const [browserBookmarks, managedIndex] = await Promise.all([
      getBrowserBookmarks(),
      readManagedIndex()
    ]);

    syncStatus.textContent =
      `浏览器书签 ${browserBookmarks.length} 个，管理器书签 ${Object.keys(managedIndex.items || {}).length} 个。`;
  } catch (error) {
    syncStatus.textContent = `读取失败：${error.message || error}`;
  }
}
