/*
 * Copyright (C) 2007-2016 Siemens AG
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or 
 * substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION 
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*******************************************************************
 *
 * @author Daniel.Peintner.EXT@siemens.com
 * @version 2016-02-03 
 * @contact Joerg.Heuer@siemens.com
 *
 * <p>Code generated by EXIdizer</p>
 * <p>Schema: schema-for-json.xsd</p>
 *
 *
 ********************************************************************/



#include "DynamicMemory.h"

#include <string.h>

#include "EXIConfig.h"
#include "EXITypes.h"
#include "ErrorCodes.h"

#if MEMORY_ALLOCATION == DYNAMIC_ALLOCATION
#include <stdlib.h>

#ifndef DYNAMIC_MEMORY_C
#define DYNAMIC_MEMORY_C


int exiAllocateDynamicStringMemory(exi_string_t* s, uint16_t length) {
	int errn = 0;
	/* allocate dynamic memory */
	s->size = length; /* length << 1; */ /* length * 2 */
	s->characters = (exi_string_character_t*) malloc(s->size * sizeof(exi_string_character_t));

	if(NULL == s->characters) {
		s->size = 0;
		errn = EXI_ERROR_OUT_OF_STRING_BUFFER;
	}

	return errn;
}

int exiAllocateDynamicBinaryMemory(exi_bytes_t* b, uint16_t length) {
	int errn = 0;
	/* allocate dynamic memory */
	b->size = length; /* length << 1; */ /* length * 2 */
	b->data = (uint8_t*) malloc(b->size * sizeof(uint8_t));

	if(NULL == b->data) {
		b->size = 0;
		errn = EXI_ERROR_OUT_OF_BYTE_BUFFER;
	}

	return errn;
}



int exiFreeDynamicStringMemory(exi_string_t* s) {
	/* free previous allocated memory, if any */
	if(s->size != 0) {
		s->size = 0;
		free(s->characters);
	}

	return 0;
}

int exiFreeDynamicBinaryMemory(exi_bytes_t* b) {
	/* free previous allocated memory, if any */
	if(b->size != 0) {
		b->size = 0;
		free(b->data);
	}

	return 0;
}


#endif

#endif /* DYNAMIC_ALLOCATION */
