#ifndef SCHEDULE32_PNG_H
#define SCHEDULE32_PNG_H

#include <wx/mstream.h>
#include <wx/image.h>
#include <wx/bitmap.h>

static const unsigned char schedule32_png[] = 
{
	0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 
	0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x20, 
	0x00, 0x00, 0x00, 0x20, 0x08, 0x06, 0x00, 0x00, 0x00, 0x73, 
	0x7A, 0x7A, 0xF4, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 
	0x73, 0x00, 0x00, 0x0B, 0x13, 0x00, 0x00, 0x0B, 0x13, 0x01, 
	0x00, 0x9A, 0x9C, 0x18, 0x00, 0x00, 0x00, 0xD5, 0x49, 0x44, 
	0x41, 0x54, 0x58, 0xC3, 0xED, 0x57, 0xC1, 0x0D, 0xC3, 0x20, 
	0x0C, 0x3C, 0x47, 0x1D, 0x02, 0x29, 0xC3, 0xF0, 0x65, 0xE3, 
	0xCE, 0xC0, 0x20, 0x11, 0x63, 0xB8, 0x8F, 0xF2, 0x20, 0xAE, 
	0x30, 0x4E, 0x54, 0xC2, 0xC7, 0x27, 0x59, 0x22, 0x06, 0x93, 
	0x8B, 0xCD, 0x11, 0x20, 0x66, 0xC6, 0x4A, 0x6C, 0x5A, 0x27, 
	0x11, 0x45, 0x22, 0xCA, 0xD5, 0xA2, 0x75, 0xD2, 0x4B, 0x71, 
	0xCC, 0xDC, 0x35, 0x00, 0x05, 0x00, 0x57, 0x2B, 0xDA, 0xD8, 
	0xBB, 0x71, 0xA4, 0x95, 0x80, 0x88, 0x58, 0x90, 0x25, 0x63, 
	0x06, 0xEC, 0x71, 0x82, 0x79, 0x04, 0x90, 0xBF, 0x6E, 0x46, 
	0xF3, 0x15, 0xDC, 0xF3, 0x59, 0xC6, 0x34, 0xBE, 0x0C, 0x20, 
	0x9E, 0xDE, 0xD9, 0x4B, 0xDD, 0x24, 0x02, 0x3F, 0x25, 0x91, 
	0x8B, 0x30, 0x88, 0xE7, 0xA3, 0xD3, 0x1E, 0x41, 0x8B, 0x0B, 
	0x5A, 0x09, 0x5A, 0xE6, 0x3B, 0x80, 0x54, 0xB3, 0x52, 0x6A, 
	0x7B, 0x1F, 0x65, 0xC0, 0x12, 0xA7, 0x95, 0xA0, 0x9D, 0xE8, 
	0x0D, 0x20, 0x34, 0x7D, 0xA1, 0xFA, 0x46, 0x04, 0x86, 0x71, 
	0x5D, 0x15, 0xC8, 0xD5, 0x3B, 0x0B, 0xAD, 0x2A, 0x36, 0x2C, 
	0xC6, 0xCB, 0xC2, 0x52, 0x6A, 0xFC, 0x6E, 0xDF, 0xE5, 0xAD, 
	0x78, 0xF9, 0xBF, 0xC0, 0x09, 0x3C, 0x81, 0xE5, 0x32, 0x74, 
	0x15, 0x38, 0x01, 0x57, 0x81, 0xAB, 0xC0, 0x09, 0xB8, 0x0A, 
	0x36, 0xE5, 0x38, 0x3D, 0x0B, 0x87, 0x76, 0x2C, 0x4F, 0xE2, 
	0x5E, 0xF7, 0x6F, 0x2B, 0x00, 0x92, 0xF9, 0x6E, 0xF8, 0x04, 
	0x3E, 0xC7, 0x0B, 0x8E, 0x0E, 0x8B, 0x8B, 0xCF, 0xE9, 0x00, 
	0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 
	0x82, 
};

static wxBitmap& schedule32_png_to_wx_bitmap()
{
	static wxMemoryInputStream memIStream( schedule32_png, sizeof( schedule32_png ) );
	static wxImage image( memIStream, wxBITMAP_TYPE_ANY );
	static wxBitmap bmp( image );
	return bmp;
};


#endif //SCHEDULE32_PNG_H
