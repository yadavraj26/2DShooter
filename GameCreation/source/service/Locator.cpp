#include"../../include/Service/Locator.h"
#include"../../include/sound/Audio.h"

std::shared_ptr<Audio> Locator::nullAudio = std::make_shared<NullAudio>();
std::shared_ptr<Audio> Locator::plActionAudio = Locator::nullAudio;
std::shared_ptr<Audio> Locator::plPickupAudio = Locator::nullAudio;