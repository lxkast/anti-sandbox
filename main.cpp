#include <iostream>
#include <dxgi.h>
#include <Windows.h>
#include <stdint.h>
#include <vector>
#include <algorithm>

const uint32_t vendor_whitelist[3]{
	0x10DE, // NVIDIA
	0x1022, // AMD
	0x8086  // Intel
};

void main() {
	IDXGIFactory* pFactory = nullptr;
	HRESULT result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory));

	IDXGIAdapter* temp_adapter = nullptr;
	std::vector<IDXGIAdapter*> vAdapters;
	for (uint32_t i = 0; pFactory->EnumAdapters(i, &temp_adapter) != DXGI_ERROR_NOT_FOUND; ++i) {
		vAdapters.push_back(temp_adapter);
	}

	// get vendor ID from each adapter
	bool matched_whitelist = false;
	for (IDXGIAdapter* adapter : vAdapters) {
		DXGI_ADAPTER_DESC adapter_desc;
		HRESULT result = adapter->GetDesc(&adapter_desc);
		
		if (result != S_OK) {
			std::cout << "Error getting desc of adapter" << std::endl;
			continue;
		}

		uint32_t vendor_id = adapter_desc.VendorId;
		std::wcout << adapter_desc.Description << " , Vendor ID: " << vendor_id << std::endl;

		// only want to check if AT LEAST one adapter is whitelisted
		// since there's other adapters that are present on both sandboxes and real machines
		if (std::find(std::begin(vendor_whitelist), std::end(vendor_whitelist), vendor_id))
			matched_whitelist = true;
	}	
	if (matched_whitelist)
		std::cout << "Whitelist matched, not running in sandbox" << std::endl;
	else
		std::cout << "Whitelist not matched, running in sandbox" << std::endl;
}