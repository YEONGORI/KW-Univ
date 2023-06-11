typedef struct
{
	int (*create)();
	int (*open)();
	int (*read)();
	int (*write)();
	int (*close)();
} bdswtable; // block device switch table

typedef struct
{
	int (*create)();
	int (*open)();
	int (*read)();
	int (*write)();
	int (*close)();
} cdswtable; // character device switch table

int main(void)
{
	cdswtable ttyIOdrv;

	// 터미널 드라이버함수 = 표준 API 함수
	ttyIOdrv.create = tty_create;
	ttyIOdrv.open = tty_open;
	ttyIOdrv.read = tty_read;
	ttyIOdrv.write = tty_write;

	cdswtable IOdrv[10];
	IOdrv[0].create = tty_create; // terminal dirver functions
	IOdrv[0].open tty_open;

	IOdrv[1].create = lpr_create; // Printer driver functions
	IOdrv[1].open = lpr_open;
}
