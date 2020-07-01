#include "MySystemError.h"

int _tmain(void) {
	_tsetlocale(LC_ALL, _T("korean"));

	SHFILEOPSTRUCT sFOs = { 0, };
	sFOs.wFunc = FO_DELETE;
	sFOs.pFrom = _T("g:\\test0");
	//sFOs.pTo = _T("g:\\test");
	SHFileOperation(&sFOs);
	
	return 0;
}