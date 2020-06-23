


ENTRY(_start)

MEMORY
{
    RAM (wx): ORIGIN = 0x00000000, LENGTH = 2048M
    ROM (rx): ORIGIN = 0x80000000, LENGTH = 1024M
}


SECTIONS
{
    secure 0x00000 : 
	{
		startup.o(.text) 
		boot.o(.*)

		. = ALIGN(16);
		. = . + 2048;
		_el3StackCpu0	= . ;
		. = . + 2048;
		_el3StackCpu1	= . ;
		. = . + 2048;
		_el3StackCpu2	= . ;
		. = . + 2048;
		_el3StackCpu3	= . ;

        startup.o(.data)

    } > RAM

}

