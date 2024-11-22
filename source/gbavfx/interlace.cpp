
#include "gbavfx/gbavfx.h"
#include "gbadef.h"

IWRAM_CODE
void gbavfx_interlace()
{
    u16 *back = (u16 *)gbavfx_color;
    if (((u32)back & 0xA000) == 0) // buffer[1]이 표시되고 있는 경우
        back += 120; // 홀수 라인 복사
    u16 *front = (u16 *)((u32)back ^ 0xA000);
    int i = 80; // 80개의 인터레이스 스캔라인

    while (i)
    {
        // DMA3 설정
		// *(volatile u32 *)0x40000DC = 0;
        *(volatile u32 *)0x40000D4 = (u32)front; // 소스 주소
        *(volatile u32 *)0x40000D8 = (u32)back;  // 목적지 주소
        // *(volatile u16 *)0x40000DC = 120;        // 전송할 16비트 단어 수
        // *(volatile u16 *)0x40000DE = (1 << 15);  // DMA 시작 (DMA Enable)
        *(volatile u32 *)0x40000DC = (1 << 31) | 120;

        // 다음 라인으로 포인터 이동 (한 라인 건너뜀)
        front += 240;
        back += 240;
        i--;

        // DMA 전송 완료 대기
        // while (*(volatile u16 *)0x40000DE & (1 << 15));
    }
}
