#include "Includes.h"

void Discord::Initialize()
{
	DiscordEventHandlers Handle;
	memset(&Handle, 0, sizeof(Handle));
	Discord_Initialize("1087520438885830786", &Handle, 1, NULL);

}

void Discord::Update()
{
	static int64_t StartTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.state = "PubgMobile 32bit";
	discordPresence.details = "Safe For Main Account";
	discordPresence.startTimestamp = StartTime;
	discordPresence.endTimestamp = NULL;
	discordPresence.largeImageKey = "";
	discordPresence.largeImageText = "";
	discordPresence.smallImageKey = "";
	discordPresence.smallImageText = "";
	discordPresence.smallImageText = "";
	discordPresence.button1Label = "Join Discord";
	discordPresence.button1Url = "";
	discordPresence.button2Label = "Join Telegram";
	discordPresence.button2Url = "";
	discordPresence.instance = 1;

	Discord_UpdatePresence(&discordPresence);
}
