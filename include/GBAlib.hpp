
//! Put function in IWRAM.
// #define IWRAM_CODE __attribute__((section(".iwram"), long_call))

//! Put function in EWRAM.
#define EWRAM_CODE __attribute__((section(".ewram"), long_call))

//! Force a variable to an \a n-byte boundary
#define ALIGN(n)	__attribute__((aligned(n)))

//! Create value with bit \a n set
#define BIT(n)				( 1<<(n) )
// --- function pointer ---
typedef void (*fnptr)(void);	//!< void foo() function pointer
typedef void (*fn_v_i)(int);	//!< void foo(int x) function pointer
typedef int (*fn_i_i)(int);		//!< int foo(int x) function pointer

typedef short       COLOR;

//! \name Main sections
//\{
#define MEM_EWRAM	0x02000000	//!< External work RAM
#define MEM_IWRAM	0x03000000	//!< Internal work RAM
#define MEM_IO		0x04000000	//!< I/O registers
#define MEM_PAL		0x05000000	//!< Palette. Note: no 8bit write !!
#define MEM_VRAM	0x06000000	//!< Video RAM. Note: no 8bit write !!
#define MEM_OAM		0x07000000	//!< Object Attribute Memory (OAM) Note: no 8bit write !!
#define MEM_ROM		0x08000000	//!< ROM. No write at all (duh)
#define MEM_SRAM	0x0E000000	//!< Static RAM. 8bit write only
//\}
// sizes in pixels
#define SCREEN_WIDTH		240
#define SCREEN_HEIGHT		160

#define M3_WIDTH			SCREEN_WIDTH
#define M3_HEIGHT			SCREEN_HEIGHT
#define M4_WIDTH			SCREEN_WIDTH
#define M4_HEIGHT			SCREEN_HEIGHT
#define M5_WIDTH			160
#define M5_HEIGHT			128
//! \name Main section sizes
//\{
#define EWRAM_SIZE	0x40000
#define IWRAM_SIZE	0x08000
#define PAL_SIZE	0x00400
#define VRAM_SIZE	0x18000
#define OAM_SIZE	0x00400
#define SRAM_SIZE	0x10000
//\}

//! \name Sub section sizes
//\{
#define PAL_BG_SIZE		0x00200		//!< BG palette size
#define PAL_OBJ_SIZE	0x00200		//!< Object palette size
#define CBB_SIZE		0x04000		//!< Charblock size
#define SBB_SIZE		0x00800		//!< Screenblock size
#define VRAM_BG_SIZE	0x10000		//!< BG VRAM size
#define VRAM_OBJ_SIZE	0x08000		//!< Object VRAM size
#define M3_SIZE			0x12C00		//!< Mode 3 buffer size
#define M4_SIZE			0x09600		//!< Mode 4 buffer size
#define M5_SIZE			0x0A000		//!< Mode 5 buffer size
#define VRAM_PAGE_SIZE	0x0A000		//!< Bitmap page size
//\}

//! \name Sub sections
//\{
#define REG_BASE		MEM_IO

#define MEM_PAL_BG		(MEM_PAL)					//!< Background palette address
#define MEM_PAL_OBJ		(MEM_PAL + PAL_BG_SIZE)		//!< Object palette address
#define MEM_VRAM_FRONT	(MEM_VRAM)					//!< Front page address
#define MEM_VRAM_BACK	(MEM_VRAM + VRAM_PAGE_SIZE)	//!< Back page address
#define MEM_VRAM_OBJ	(MEM_VRAM + VRAM_BG_SIZE)	//!< Object VRAM address
//\}

//! \name Interrupt / System registers
//\{
#define REG_IE				*(unsigned short*)(REG_BASE+0x0200)	//!< IRQ enable
#define REG_IF				*(unsigned short*)(REG_BASE+0x0202)	//!< IRQ status/acknowledge
#define REG_WAITCNT			*(unsigned short*)(REG_BASE+0x0204)	//!< Waitstate control
#define REG_IME				*(unsigned short*)(REG_BASE+0x0208)	//!< IRQ master enable
#define REG_PAUSE			*(unsigned short*)(REG_BASE+0x0300)	//!< Pause system (?)
//\}

// 0300:7ff[y] is mirrored at 03ff:fff[y], which is why this works out:
#define REG_IFBIOS			*(unsigned short*)(REG_BASE-0x0008)	//!< IRQ ack for IntrWait functions
#define REG_RESET_DST		*(unsigned short*)(REG_BASE-0x0006)	//!< Destination for after SoftReset
#define REG_ISR_MAIN		*(fnptr*)(REG_BASE-0x0004)	//!< IRQ handler address
//\}

//! \name Display registers
//\{
#define REG_DISPCNT			*(unsigned int*)(REG_BASE+0x0000)	//!< Display control
#define REG_DISPSTAT		*(unsigned short*)(REG_BASE+0x0004)	//!< Display status
#define REG_VCOUNT			*(unsigned short*)(REG_BASE+0x0006)	//!< Scanline count
//\}

#define DCNT_MODE0				 0	//!< Mode 0; bg 0-4: reg
#define DCNT_MODE1			0x0001	//!< Mode 1; bg 0-1: reg; bg 2: affine
#define DCNT_MODE2			0x0002	//!< Mode 2; bg 2-3: affine
#define DCNT_MODE3			0x0003	//!< Mode 3; bg2: 240x160\@16 bitmap
#define DCNT_MODE4			0x0004	//!< Mode 4; bg2: 240x160\@8 bitmap
#define DCNT_MODE5			0x0005	//!< Mode 5; bg2: 160x128\@16 bitmap
#define DCNT_PAGE			0x0010	//!< Page indicator

#define DCNT_BG0			0x0100	//!< Enable bg 0
#define DCNT_BG1			0x0200	//!< Enable bg 1
#define DCNT_BG2			0x0400	//!< Enable bg 2
#define DCNT_BG3			0x0800	//!< Enable bg 3

#define pal_bg_mem		((COLOR*)MEM_PAL)

// // Fast memcpy/set
// void memset16(void *dst, unsigned short hw, unsigned int hwcount);
// void memcpy16(void *dst, const void* src, unsigned int hwcount);

// IWRAM_CODE void memset32(void *dst, unsigned int wd, unsigned int wcount);
// IWRAM_CODE void memcpy32(void *dst, const void* src, unsigned int wcount);

// typedef struct IRQ_REC	
// {
// 	unsigned int flag;	//!< Flag for interrupt in REG_IF, etc
// 	fnptr isr;	//!< Pointer to interrupt routine
// } IRQ_REC;

// typedef struct IRQ_SENDER
// {
// 	unsigned short reg_ofs;	//!< sender reg - REG_BASE
// 	unsigned short flag;		//!< irq-bit in sender reg
// } ALIGN4 IRQ_SENDER;

// typedef enum eIrqIndex
// {
// 	II_VBLANK=0,II_HBLANK,	II_VCOUNT,	II_TIMER0,
// 	II_TIMER1,	II_TIMER2,	II_TIMER3,	II_SERIAL,
// 	II_DMA0,	II_DMA1,	II_DMA2,	II_DMA3,
// 	II_KEYPAD,	II_GAMEPAK,	II_MAX
// } eIrqIndex;

// IRQ_REC __isr_table[II_MAX+1];

// static const IRQ_SENDER __irq_senders[] = 
// {
// 	{ 0x0004, 0x0008 },		// REG_DISPSTAT,	DSTAT_VBL_IRQ
// 	{ 0x0004, 0x0010 },		// REG_DISPSTAT,	DSTAT_VHB_IRQ
// 	{ 0x0004, 0x0020 },		// REG_DISPSTAT,	DSTAT_VCT_IRQ
// 	{ 0x0102, 0x0040 },		// REG_TM0CNT,		TM_IRQ
// 	{ 0x0106, 0x0040 },		// REG_TM1CNT,		TM_IRQ
// 	{ 0x010A, 0x0040 },		// REG_TM2CNT,		TM_IRQ
// 	{ 0x010E, 0x0040 },		// REG_TM3CNT,		TM_IRQ
// 	{ 0x0128, 0x4000 },		// REG_SIOCNT		SIO_IRQ
// 	{ 0x00BA, 0x4000 },		// REG_DMA0CNT_H,	DMA_IRQ>>16
// 	{ 0x00C6, 0x4000 },		// REG_DMA1CNT_H,	DMA_IRQ>>16
// 	{ 0x00D2, 0x4000 },		// REG_DMA2CNT_H,	DMA_IRQ>>16
// 	{ 0x00DE, 0x4000 },		// REG_DMA3CNT_H,	DMA_IRQ>>16
// 	{ 0x0132, 0x4000 },		// REG_KEYCNT,		KCNT_IRQ
// 	{ 0x0000, 0x0000 },		// cart: none
// };

// IWRAM_CODE void isr_master(void);
// IWRAM_CODE void isr_master_nest(void);

// void irq_init(fnptr isr)
// {
// 	REG_IME= 0;	

// 	// clear interrupt table (just in case)
// 	// memset32(__isr_table, 0, (II_MAX+1)*sizeof(IRQ_REC)/4);

// 	REG_ISR_MAIN= (isr) ? isr : (fnptr)isr_master;

// 	REG_IME= 1;
// }

// fnptr irq_add(enum eIrqIndex irq_id, fnptr isr)
// {
// 	unsigned short ime= REG_IME;
// 	REG_IME= 0;

// 	int ii;
// 	unsigned short irq_flag= BIT(irq_id);
// 	fnptr old_isr;
// 	IRQ_REC	*pir= __isr_table;

// 	// Enable irq
// 	const IRQ_SENDER *sender= &__irq_senders[irq_id];
// 	*(unsigned short*)(REG_BASE+sender->reg_ofs) |= sender->flag;
// 	REG_IE |= irq_flag;

// 	// Search for previous occurance, or empty slot
// 	for(ii=0; pir[ii].flag; ii++)
// 		if(pir[ii].flag == irq_flag)
// 			break;
	
// 	old_isr= pir[ii].isr;
// 	pir[ii].isr= isr;
// 	pir[ii].flag= irq_flag;

// 	REG_IME= ime;
// 	return old_isr;
// }

void init_palettes()
{
	static unsigned short	palette[] = {0x0000, 0x56B5, 0x318C, 0x6F7B, 0x64C8, 0x6E28, 0x6768, 0x4626, 0x1A28, 0x2368, 
    0x2379, 0x1A39, 0x463B, 0x20D9, 0x64D9, 0x6E39, 0x739C, 0x6F7B, 0x6F7B, 0x6318, 
    0x5AD6, 0x56B5, 0x4A52, 0x4210, 0x39CE, 0x39CE, 0x318C, 0x294A, 0x2108, 0x18C6, 
    0x1084, 0x1084, 0x7800, 0x7000, 0x7000, 0x6800, 0x6000, 0x5800, 0x5800, 0x5000, 
    0x4800, 0x4000, 0x3800, 0x3800, 0x3000, 0x2800, 0x2000, 0x2000, 0x7B5A, 0x7AD6, 
    0x7A52, 0x79CE, 0x794A, 0x7908, 0x7884, 0x7800, 0x7A8A, 0x7A48, 0x7A04, 0x79C0, 
    0x7180, 0x6180, 0x5940, 0x4900, 0x7BDA, 0x7BD6, 0x7BD2, 0x7BCE, 0x7BCA, 0x7BC8, 
    0x7BC4, 0x7BC0, 0x7340, 0x6300, 0x5A80, 0x4A40, 0x4200, 0x3980, 0x2940, 0x2100, 
    0x6BCA, 0x63C8, 0x5BC4, 0x53C0, 0x4B80, 0x4300, 0x3AC0, 0x3240, 0x6BDA, 0x5BD6, 
    0x4BD2, 0x43CE, 0x33CA, 0x23C8, 0x13C4, 0x03C0, 0x03C0, 0x0380, 0x0380, 0x0340, 
    0x0300, 0x02C0, 0x02C0, 0x0280, 0x0240, 0x0200, 0x01C0, 0x01C0, 0x0180, 0x0140, 
    0x0100, 0x0100, 0x6BDE, 0x5BDE, 0x4BDE, 0x3BDE, 0x2BDE, 0x23DE, 0x13DE, 0x03DE, 
    0x039C, 0x0318, 0x02D6, 0x0252, 0x0210, 0x01CE, 0x014A, 0x0108, 0x2ADE, 0x22DE, 
    0x129E, 0x025E, 0x021C, 0x01D8, 0x0196, 0x0152, 0x6B5E, 0x5ADE, 0x4A5E, 0x3A1E, 
    0x299E, 0x211E, 0x109E, 0x001E, 0x001E, 0x001C, 0x001C, 0x001A, 0x0018, 0x0016, 
    0x0016, 0x0014, 0x0012, 0x0010, 0x000E, 0x000E, 0x000C, 0x000A, 0x0008, 0x0008, 
    0x7B5E, 0x72DE, 0x6A5E, 0x69DE, 0x615E, 0x591E, 0x589E, 0x501E, 0x481C, 0x4018, 
    0x3816, 0x3012, 0x2810, 0x200E, 0x180A, 0x1008, 0x7B5E, 0x7ADE, 0x7A5E, 0x79DE, 
    0x795E, 0x791E, 0x789E, 0x781E, 0x701C, 0x6018, 0x5816, 0x4812, 0x4010, 0x300E, 
    0x280A, 0x2008, 0x7B9A, 0x7B5A, 0x7B58, 0x7316, 0x72D4, 0x6AD2, 0x6A92, 0x6250, 
    0x6250, 0x5A0E, 0x59CC, 0x51CC, 0x518A, 0x518A, 0x4948, 0x4948, 0x4106, 0x40C6, 
    0x38C4, 0x38C4, 0x3884, 0x3082, 0x3042, 0x2842, 0x2842, 0x2040, 0x2000, 0x1800, 
    0x1800, 0x1000, 0x1000, 0x1000, 0x794A, 0x7AD0, 0x7BD0, 0x43D0, 0x43DE, 0x421E, 
    0x5A1E, 0x7A1E, 0x6084, 0x6104, 0x61C4, 0x6244, 0x6304, 0x4B04, 0x3B04, 0x2304, 
    0x1306, 0x130A, 0x1310, 0x1316, 0x1298, 0x11D8, 0x1158, 0x1098, 0x2898, 0x4098, 
    0x5898, 0x6094, 0x6090, 0x608A, 0x6084, 0x7BDE};
    // *pal_bg_mem = palette;
	for (int i = 0; i < 256; ++i) {
		pal_bg_mem[i] = palette[i];
	}

}

// INLINE void m4_plot(int x, int y, u8 clrid)
// {
// 	unsigned short *dst= &vid_page[(y*M4_WIDTH+x)>>1];
// 	if(x&1)
// 		*dst= (*dst& 0xFF) | (clrid<<8);
// 	else
// 		*dst= (*dst&~0xFF) |  clrid;
// }

//! First page array
#define vid_mem_front	((COLOR*)MEM_VRAM)

//! Second page array
#define vid_mem_back	((COLOR*)MEM_VRAM_BACK)
COLOR *vid_page= vid_mem_back;

COLOR *vid_flip(void)
{
	vid_page= (COLOR*)((unsigned int)vid_page ^ VRAM_PAGE_SIZE);
	REG_DISPCNT ^= DCNT_PAGE;	// update control register	

	return vid_page;
}