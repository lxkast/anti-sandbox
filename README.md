# anti-sandbox
Simple sandbox detection in C++
---
# How it works
*This technique is not my own and is an implementation described by [this blog post by Intezer](https://intezer.com/blog/research/babble-babble-babble-babble-babble-babble-babbleloader/).*

By importing `dxgi.dll` we can create an `IDXGIFactory` object to enumerate the display adapters on the system, comparing the vendor IDs of each to a whitelist for Intel, AMD and NVIDIA.
If not a single display adapter's vendor ID matches a whitelisted one, it is highly likely to not be running on a real machine.
# Requirements
C++17, link with `dxgi.lib`
