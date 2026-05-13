import { callChromeApi, getTabsApi } from "./api.js";

const BROWSER_BOOKMARK_URLS = {
  chrome: "chrome://bookmarks/",
  edge: "edge://favorites/",
  firefox: null,
  opera: "opera://bookmarks/",
  brave: "chrome://bookmarks/",
  chromium: "chrome://bookmarks/",
  unknown: null
};

export function detectBrowser(
  userAgent = globalThis.navigator?.userAgent || "",
  brands = globalThis.navigator?.userAgentData?.brands || []
) {
  const brandBrowser = detectBrowserFromBrands(brands);

  if (brandBrowser) {
    return browserInfo(brandBrowser.id, brandBrowser.name);
  }

  const ua = userAgent.toLowerCase();

  if (/\bfirefox\//i.test(userAgent)) {
    return browserInfo("firefox", "Firefox");
  }

  if (/\bedg(e|a|ios)?\//i.test(userAgent)) {
    return browserInfo("edge", "Microsoft Edge");
  }

  if (/\bopr\//i.test(userAgent) || ua.includes("opera")) {
    return browserInfo("opera", "Opera");
  }

  if (/\bchrome\//i.test(userAgent)) {
    return browserInfo("chrome", "Google Chrome");
  }

  if (/\bchromium\//i.test(userAgent)) {
    return browserInfo("chromium", "Chromium");
  }

  return browserInfo("unknown", "Unknown Browser");
}

function browserInfo(id, name) {
  const nativeBookmarkUrl = BROWSER_BOOKMARK_URLS[id] || null;

  return {
    id,
    name,
    kind: id,
    isChromium: ["chrome", "edge", "opera", "brave", "chromium"].includes(id),
    nativeBookmarkUrl,
    nativeBookmarkManagerUrl: nativeBookmarkUrl,
    supportsNativeBookmarkManagerUrl: Boolean(nativeBookmarkUrl)
  };
}

export async function openNativeBookmarkManager(browser = detectBrowser()) {
  const url = browser.nativeBookmarkUrl;

  if (!url) {
    return {
      ok: false,
      url,
      browser,
      method: browser.id === "firefox" ? "unsupported" : "manual",
      message:
        browser.id === "firefox"
          ? "Firefox WebExtensions do not expose a reliable native bookmark manager URL."
          : "Unable to determine a native bookmark manager URL for this browser."
    };
  }

  try {
    const tabs = getTabsApi();
    await callChromeApi(tabs.create, tabs, { active: true, url });

    return {
      ok: true,
      url,
      browser,
      method: "tabs.create"
    };
  } catch (error) {
    const windowResult = openWithWindow(url);

    if (windowResult.ok) {
      return {
        ok: true,
        url,
        browser,
        method: "window.open"
      };
    }

    return {
      ok: false,
      url,
      browser,
      method: "manual",
      error: error?.message || windowResult.error?.message || String(error),
      message:
        "The browser blocked opening its internal bookmark manager URL. Ask the user to open the URL manually."
    };
  }
}

function detectBrowserFromBrands(brands) {
  const brandText = brands
    .map((brand) => brand.brand.toLowerCase())
    .join(" ");

  if (brandText.includes("microsoft edge")) {
    return { id: "edge", name: "Microsoft Edge" };
  }

  if (brandText.includes("opera")) {
    return { id: "opera", name: "Opera" };
  }

  if (brandText.includes("google chrome")) {
    return { id: "chrome", name: "Google Chrome" };
  }

  if (brandText.includes("chromium")) {
    return { id: "chromium", name: "Chromium" };
  }

  return null;
}

function openWithWindow(url) {
  try {
    if (typeof globalThis.open !== "function") {
      return { ok: false, error: new Error("window.open is unavailable.") };
    }

    return { ok: globalThis.open(url, "_blank", "noopener,noreferrer") !== null };
  } catch (error) {
    return { ok: false, error };
  }
}
