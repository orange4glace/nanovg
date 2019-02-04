const electron = window.require('electron');
const basepath = electron.remote.app.getAppPath();
console.log(`[Starter/Common] basepath=${basepath}`);

// Load native Olive module

const module = window.require(`${basepath}/build/Release/nanovg_node_webgl.node`);