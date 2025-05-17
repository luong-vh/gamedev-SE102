#include "CloudBlock.h"

void CCloudBlock::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_CLOUD_BLOCK)->Render(x, y);
}
