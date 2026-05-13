# Better Bookmark Manager

一个本地优先的浏览器书签管理扩展，当前主要支持 Chrome 和 Microsoft Edge。

## 核心功能

- 自动识别当前浏览器。
- 在 Chrome 中打开 `chrome://bookmarks/`。
- 在 Edge 中打开 `edge://favorites/`。
- 读取当前浏览器的原生书签树。
- 获取并展示书签对应网站的 favicon。当前实现使用 `favicon.im`，不从 Chrome/Edge 原生书签图标缓存读取。
- 左侧可在“浏览器书签”和“管理器书签”之间切换。
- 浏览器书签为只读模式，可手动检查新增或删除，不会被自动写入管理器。
- 管理器书签独立保存在插件中，支持手动添加，也支持从浏览器书签中勾选导入；已存在的书签会标注并在导入时跳过。
- 管理器支持搜索、筛选、打开书签、行内编辑标题和网址、编辑标签和备注。只有鼠标停留在书签标题文字上时才会打开对应网站。
- 支持从管理器移除书签，不会删除浏览器原生书签。
- 支持置顶书签。
- 支持拖动调整顺序。置顶书签只能在置顶区域内排序，普通书签只能在普通区域内排序。

## 项目结构

```text
manifest.json
package.json
src/
  api.js                # Chrome / browser API Promise 包装
  background.js         # 安装、启动、书签事件监听和消息入口
  bookmarkSync.js       # 书签读取、扁平化、索引补齐
  browserDetection.js   # 浏览器识别与原生书签页打开
  manager.html          # 完整管理页
  manager.js
  popup.html            # 扩展弹窗入口
  popup.js
  styles.css
TESTING.md
```

当前版本不需要构建。`manifest.json` 直接指向 `src/popup.html`、`src/manager.html` 和 `src/background.js`。

## 本地加载

### Chrome

1. 打开 `chrome://extensions/`。
2. 开启“开发者模式”。
3. 点击“加载已解压的扩展程序”。
4. 选择目录：`D:\Test`。
5. 点击扩展图标，或在扩展详情中打开“扩展程序选项”。

如果修改过 `manifest.json`，需要在扩展管理页点击“重新加载”。站点图标功能需要访问书签对应网站的图标地址，因此浏览器可能会提示该扩展可读取访问的网站数据。

### Microsoft Edge

1. 打开 `edge://extensions/`。
2. 开启“开发人员模式”。
3. 点击“加载解压缩的扩展”。
4. 选择目录：`D:\Test`。
5. 点击扩展图标，或在扩展详情中打开“扩展选项”。

## 开发检查

本项目目前没有外部依赖。可运行语法检查：

```powershell
npm run check
```

也可以逐个检查：

```powershell
node --check src/background.js
node --check src/manager.js
node --check src/popup.js
```

## 数据说明

扩展不会替代浏览器原生书签系统。原生书签仍保存在当前浏览器 profile 中，扩展只在 `chrome.storage.local` 中保存管理页索引、标签、备注和状态。

浏览器书签和管理器书签现在是隔离的。浏览器书签只读展示，管理器书签只保存在插件索引中；从浏览器书签导入时会复制一份到管理器，若同源书签或相同 URL 已存在则跳过。管理器里的编辑和移除不会修改或删除浏览器原生书签。

站点图标不会从 Chrome/Edge 的原生书签图标缓存读取。管理页会直接用 `Image` 对象加载 `favicon.im`：`https://favicon.im/zh/域名`。如果 200ms 内没有加载完成，则保留域名首字母。

索引 key：

```text
betterBookmarkManager.index.v1
```

如果要验证“浏览器有但管理页没有时自动补齐”，可以在扩展页面开发者工具中清空索引：

```js
chrome.storage.local.remove("betterBookmarkManager.index.v1");
```

然后重新打开 popup、管理页，或点击管理页里的“重新同步”。
