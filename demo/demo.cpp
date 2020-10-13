#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <iostream>

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*FuncType_ProDrvInit)();

/**
 * @brief Loading dynamic library.
 */
void *LoadDLL(char *dllname)
{
	void *handle;
	handle = dlopen(dllname, RTLD_LAZY | RTLD_GLOBAL);
	if (!handle) {
		printf("%s->%s\n", dllname, dlerror());
		return NULL;
	}

	return handle;
}

/**
 * @brief Close dynamic library.
 */
int ReLoadDLL(void *handle)
{
	return dlclose(handle);
}

/**
 *@brief Get api from dynamic library.
 */
void *GetDLLAPI(void *handle, const char *symbol)
{
	void *api;
	api = (void*)dlsym(handle, symbol);
	if (!api) {
		printf("%s->%s%d\n", symbol, dlerror(), __LINE__);
		ReLoadDLL(handle);
		return NULL;
	}

	return api;
}

#ifdef __cplusplus
}
#endif

int main()
{
	void *handle;
	void *api;

    handle = LoadDLL((char *)"./libpro.so.1");
	if (!handle) {
		printf("%s->%d err\n", __func__, __LINE__);
		return -13;
	}

	FuncType_ProDrvInit DrvInit = (FuncType_ProDrvInit) GetDLLAPI(handle, "DrvInit");
	if (!DrvInit) {
		printf("%s->%d err\n", __func__, __LINE__);
		return -13;
	}

	// Run pro.
	DrvInit();

	return 0;
}
