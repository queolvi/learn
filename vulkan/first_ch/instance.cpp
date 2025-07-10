typedef struct VkInstanceCreateInfo {
VkStructureType		sType;
const void* 		pNext;
vkInstanceCreateFlags 	flags;
const vkApplicationInfo* pApplication;
uint32_t enableLayerCount;
const char* const* ppEnabledLayerNames;
uint32_t enabledExtensionsCount;
const char* const* ppenabledExtensionNames;
} VkInstanceCreateInfo;



VkResult vkCreateInstance (
const vkInstanceCreateInfo* pCreateInfo,
const vkAllocationCallbacks* pAllocator,
VkInstance *;)
