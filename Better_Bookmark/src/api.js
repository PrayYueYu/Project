export const extensionApi = globalThis.browser || globalThis.chrome;

export function getRuntime() {
  if (!extensionApi?.runtime) {
    throw new Error("Extension runtime API is not available.");
  }

  return extensionApi.runtime;
}

export function getTabsApi() {
  if (!extensionApi?.tabs) {
    throw new Error("Tabs API is not available.");
  }

  return extensionApi.tabs;
}

export function getBookmarksApi() {
  if (!extensionApi?.bookmarks) {
    throw new Error("Bookmarks API is not available.");
  }

  return extensionApi.bookmarks;
}

export function getStorageArea() {
  if (!extensionApi?.storage?.local) {
    throw new Error("Storage API is not available.");
  }

  return extensionApi.storage.local;
}

export function callChromeApi(fn, context, ...args) {
  return new Promise((resolve, reject) => {
    try {
      const maybePromise = fn.call(context, ...args, (result) => {
        const lastError = extensionApi?.runtime?.lastError;

        if (lastError) {
          reject(new Error(lastError.message));
          return;
        }

        resolve(result);
      });

      if (maybePromise && typeof maybePromise.then === "function") {
        maybePromise.then(resolve, reject);
      }
    } catch (error) {
      reject(error);
    }
  });
}

export async function storageGet(defaults) {
  const storage = getStorageArea();

  if (typeof browser !== "undefined" && browser.storage?.local) {
    return storage.get(defaults);
  }

  return callChromeApi(storage.get, storage, defaults);
}

export async function storageSet(value) {
  const storage = getStorageArea();

  if (typeof browser !== "undefined" && browser.storage?.local) {
    return storage.set(value);
  }

  return callChromeApi(storage.set, storage, value);
}
