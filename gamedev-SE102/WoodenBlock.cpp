#include "WoodenBlock.h"

void CWoodenBlock::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_WOODEN_BLOCK)->Render(x, y);
}
