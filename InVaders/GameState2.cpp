#include "stdafx.h"
#include "GameState2.h"

void GameState2::initKeybinds()
{
	std::ifstream ifs("config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();
}


void GameState2::initPlatform()
{
	this->direction.x = 0.f;
	this->direction.y = 0.f;
	//Ground
	this->platforms.push_back(new Platform(sf::Vector2f(0.f, 472.f), sf::Vector2f(143.f, 245.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(158.f, 540.f), sf::Vector2f(90.f, 176.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(245.f, 584.f), sf::Vector2f(769.f, 133.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(1012.f, 530.f), sf::Vector2f(110.f, 179.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(1121.f, 474.f), sf::Vector2f(122.f, 376.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(1261.f, 2196.f), sf::Vector2f(513.f, 135.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(891.f, 717.f), sf::Vector2f(115.f, 573.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(1778.f, 527.f), sf::Vector2f(251.f, 172.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(1778.f, 696.f), sf::Vector2f(253.f, 320.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(1768.f, 2196.f), sf::Vector2f(3637.f, 53.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(1651.f, 467.f), sf::Vector2f(313.f, 59.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(2038.f, 577.f), sf::Vector2f(732.f, 32.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(10.f, 2134.f), sf::Vector2f(810.f, 188.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(823.f, 2108.f), sf::Vector2f(60.f, 40.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(884.f, 2082.f), sf::Vector2f(246.f, 50.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(1130.f, 2056.f), sf::Vector2f(59.f, 35.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(1187.f, 2030.f), sf::Vector2f(73.f, 295.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(1237.f, 1972.f), sf::Vector2f(156.f, 50.F), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(10.f, 2134.f), sf::Vector2f(810.f, 188.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(10.f, 2134.f), sf::Vector2f(810.f, 188.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(1267.f, 692.f), sf::Vector2f(124, 26), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(1644.f, 846.f), sf::Vector2f(124, 26), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(1250.f, 1072.f), sf::Vector2f(124, 40), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(1644.f, 1744.f), sf::Vector2f(124, 26), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(1644.f, 1292.f), sf::Vector2f(124, 26), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(1259.f, 1518.f), sf::Vector2f(124, 26), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(1010.f, 1182.f), sf::Vector2f(253.f, 562.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(1133.f, 1152.f), sf::Vector2f(131.f, 36.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(1201.f, 1095.f), sf::Vector2f(60.f, 46.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(824.f, 1736.f), sf::Vector2f(310.f, 122.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(1770.f, 1292.f), sf::Vector2f(257.f, 619.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(2000.f, 1292.f), sf::Vector2f(1283.f, 131.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(3307.f, 1292.f), sf::Vector2f(261.f, 613.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(3564.f, 1520.f), sf::Vector2f(130.f, 53.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(3945.f, 1743.f), sf::Vector2f(130.f, 53.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(3948.f, 1292.f), sf::Vector2f(136.f, 53.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(3561.f, 1966.f), sf::Vector2f(139.f, 56.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(4073.f, 1292.f), sf::Vector2f(259.f, 615.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(4330.f, 1292.f), sf::Vector2f(516.f, 110.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(4845.f, 1245.f), sf::Vector2f(498.f, 630.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(4911.f, 1186.f), sf::Vector2f(188.f, 54.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(5089.f, 1186.f), sf::Vector2f(157.f, 59.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(5248.f, 1209.f), sf::Vector2f(35.f, 55.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(5287.f, 1242.f), sf::Vector2f(1662.f, 76.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(5287.f, 1242.f), sf::Vector2f(1662.f, 76.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(6947.f, 1210.f), sf::Vector2f(67.f, 89.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(6982.f, 1183.f), sf::Vector2f(469.f, 669.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(6890.f, 1607.f), sf::Vector2f(559.f, 251.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(6993.f, 2082.f), sf::Vector2f(521.f, 246.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(6957.f, 2113.f), sf::Vector2f(81.f, 129.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(6931.f, 2142.f), sf::Vector2f(40.f, 100.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(6253.f, 2190.f), sf::Vector2f(679.f, 133.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(6127.f, 1608.f), sf::Vector2f(125.f, 713.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(6894.f, 2168.f), sf::Vector2f(43.f, 83.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(7517.f, 2246.f), sf::Vector2f(383.f, 81.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(7900.f, 2080.f), sf::Vector2f(228.f, 242.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(8124.f, 2115.f), sf::Vector2f(27.f, 60.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(8152.f, 2137.f), sf::Vector2f(36.f, 60.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(8190.f, 2167.f), sf::Vector2f(36.f, 60.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(8281.f, 2192.f), sf::Vector2f(2756.f, 131.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(11387.f, 2235.f), sf::Vector2f(102.f, 303.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(10841.f, 1970.f), sf::Vector2f(196.f, 62.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(11101.f, 2082.f), sf::Vector2f(278.f, 242.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(11407.f, 2137.f), sf::Vector2f(835.f, 191.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(11474.f, 2174.f), sf::Vector2f(312.f, 117.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(10966.f, 1181.f), sf::Vector2f(256.f, 565.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(10456.f, 1744.f), sf::Vector2f(135.f, 59.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(10973.f, 2025.f), sf::Vector2f(110.f, 299.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(10844.f, 1070.f), sf::Vector2f(140.f, 55.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(10010.f, 1299.f), sf::Vector2f(457.f, 609.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(8220.f, 1299.f), sf::Vector2f(1997.f, 436.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(8097.f, 1246.f), sf::Vector2f(127.f, 503.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(7964.f, 1180.f), sf::Vector2f(137.f, 570.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(10457.f, 1299.f), sf::Vector2f(137.f, 54.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(10841.f, 1521.f), sf::Vector2f(134.f, 42.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(10970.f, 1135.f), sf::Vector2f(137.f, 614.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(11102.f, 1187.f), sf::Vector2f(131.f, 677.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(11224.f, 952.f), sf::Vector2f(198.f, 272.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(10459.f, 852.f), sf::Vector2f(139.f, 60.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(10204.f, 576.f), sf::Vector2f(253.f, 440.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(10272.f, 476.f), sf::Vector2f(318.f, 61.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(10841.f, 696.f), sf::Vector2f(137.f, 16.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(10972.f, 471.f), sf::Vector2f(159.f, 377.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(11100.f, 527.f), sf::Vector2f(127.f, 428.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(11229.f, 587.f), sf::Vector2f(776.f, 135.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(11999.f, 543.f), sf::Vector2f(86.f, 173.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(12067.f, 480.f), sf::Vector2f(198.f, 234.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(4842.f, 2167.f), sf::Vector2f(40.f, 30.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(4882.f, 2138.f), sf::Vector2f(40.f, 30.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(4915.f, 2112.f), sf::Vector2f(40.f, 30.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(4950.f, 2082.f), sf::Vector2f(151.f, 30.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(5098.f, 2082.f), sf::Vector2f(150.f, 30.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(5250.f, 2210.f), sf::Vector2f(34.f, 71.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(5287.f, 2136.f), sf::Vector2f(126.f, 176.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(5407.f, 2193.f), sf::Vector2f(68.f, 114.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(5475.f, 2250.f), sf::Vector2f(388.f, 73.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(5862.f, 2192.f), sf::Vector2f(64.f, 101.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(5925.f, 2135.f), sf::Vector2f(82.f, 122.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(5988.f, 1612.f), sf::Vector2f(60.f, 714.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(8287.f, 585.f), sf::Vector2f(1918.f, 256), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(8254.f, 563.f), sf::Vector2f(36.f, 30.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(8222.f, 535.f), sf::Vector2f(28.f, 30.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(7967.f, 487.f), sf::Vector2f(256.f, 250.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(7967.f, 667.f), sf::Vector2f(253.f, 296.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(6991.f, 479.f), sf::Vector2f(461.f, 482.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(6947.f, 712.f), sf::Vector2f(65.f, 251.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(6962.f, 507.f), sf::Vector2f(42.f, 55.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(6931.f, 534.f), sf::Vector2f(42.f, 55.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(6897.f, 562.f), sf::Vector2f(42.f, 55.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(6832.f, 585.f), sf::Vector2f(78.f, 57.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(5290.f, 630.f), sf::Vector2f(1665.f, 217.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(5356.f, 583.f), sf::Vector2f(61.f, 50.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(5293.f, 533.f), sf::Vector2f(31.f, 50.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(5261.f, 505.f), sf::Vector2f(31.f, 50.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(4614.f, 472.f), sf::Vector2f(645.f, 237.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(4188.f, 472.f), sf::Vector2f(495.f, 237.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(4156.f, 503.f), sf::Vector2f(48.f, 60.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(4120.f, 532.f), sf::Vector2f(48.f, 60.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(4088.f, 559.f), sf::Vector2f(48.f, 60.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(4056.f, 587.f), sf::Vector2f(48.f, 60.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(4025.f, 614.f), sf::Vector2f(48.f, 60.f), "stairL"));
	this->platforms.push_back(new Platform(sf::Vector2f(2802.f, 637.f), sf::Vector2f(1284.f, 209.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(2770.f, 611.f), sf::Vector2f(34.f, 30.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(0.f, 69.f), sf::Vector2f(2566.f, 120.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(2806.f, 359.f), sf::Vector2f(1097.f, 61.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(3761.f, 0.f), sf::Vector2f(136.f, 354.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(3839.f, 0.f), sf::Vector2f(1408.f, 248.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(6956.f, 0.f), sf::Vector2f(494.f, 248.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(7449.f, 0.f), sf::Vector2f(524.f, 79.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(7970.f, 0.f), sf::Vector2f(197.f, 248.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(8154.f, 0.f), sf::Vector2f(327.f, 305.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(8475.f, 136.f), sf::Vector2f(138.f, 58.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(8858.f, 358.f), sf::Vector2f(138.f, 58.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(8987.f, 0.f), sf::Vector2f(257.f, 299.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(9236.f, 86.f), sf::Vector2f(3007.f, 107.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(11221.f, 1610.f), sf::Vector2f(189.f, 249.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(8221.f, 792.f), sf::Vector2f(130.f, 223.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(8862.f, 848.f), sf::Vector2f(715.f, 173.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(10077.f, 855.f), sf::Vector2f(146.f, 166.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(2546.f, 840.f), sf::Vector2f(255.f, 180.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(2543.f, 1740.f), sf::Vector2f(255.f, 178.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(3306.f, 714.f), sf::Vector2f(265.f, 306.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(4076.f, 689.f), sf::Vector2f(260.f, 335.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(4843.f, 714.f), sf::Vector2f(443.f, 246.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(6952.f, 711.f), sf::Vector2f(502.f, 255.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(8229.f, 1637.f), sf::Vector2f(126.f, 278.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(8858.f, 1678.f), sf::Vector2f(136.f, 240.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(10016.f, 1678.f), sf::Vector2f(194.f, 240.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(2542.f, 0.f), sf::Vector2f(728.f, 83.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(3632.f, 133.f), sf::Vector2f(136.f, 58.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(1008.f, 745.f), sf::Vector2f(125.f, 216.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(5253.f, 302.f), sf::Vector2f(70.f, 60.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(5295.f, 285.f), sf::Vector2f(64.f, 75.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(5235.f, 249.f), sf::Vector2f(80.f, 70.f), "stairR"));
	this->platforms.push_back(new Platform(sf::Vector2f(6831.f, 249.f), sf::Vector2f(190.f, 54.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(12187.f, 249.f), sf::Vector2f(36.f, 224.f), "door"));
	this->platforms.push_back(new Platform(sf::Vector2f(12239.f, 1733.f), sf::Vector2f(151.f, 471.f), "floor"));
	this->platforms.push_back(new Platform(sf::Vector2f(12247.f, 241.f), sf::Vector2f(142.f, 263.f), "floor"));

}

void GameState2::initVariables()
{
	this->score = 0;
	this->changeColor = 255;
	this->haveKey = false;
	this->isPressed = false;
}

void GameState2::initBackground()
{
	if (!this->backgroundTexture.loadFromFile("Texture/state2_background.png"))
		std::cout << "ERROR::GAME::Could not load bg.png!" << "\n";
	this->background.setTexture(this->backgroundTexture);
	this->background.setScale(4.f, 3.5f);
}

void GameState2::initMusic()
{
	this->bg_music.openFromFile("Resources/Sound Effects/state2_bg_music.ogg");
	this->bg_music.setLoop(true);
	this->bg_music.setVolume(10.f);
	this->bg_music.play();
}

void GameState2::initSoundEffects()
{
	this->soundEffects["PICKUP_COIN"] = new sf::SoundBuffer;
	this->soundEffects["PICKUP_COIN"]->loadFromFile("Resources/Sound Effects/pick_up_coin.wav");
	this->soundEffects["PICKUP_POO"] = new sf::SoundBuffer;
	this->soundEffects["PICKUP_POO"]->loadFromFile("Resources/Sound Effects/pick_up_poo.wav");
	this->soundEffects["PICKUP_CHICKEN"] = new sf::SoundBuffer;
	this->soundEffects["PICKUP_CHICKEN"]->loadFromFile("Resources/Sound Effects/pick_up_chicken.wav");
	this->soundEffects["PICKUP_HEALTH"] = new sf::SoundBuffer;
	this->soundEffects["PICKUP_HEALTH"]->loadFromFile("Resources/Sound Effects/pick_up_item.wav");
	this->soundEffects["DOOR_OPEN"] = new sf::SoundBuffer;
	this->soundEffects["DOOR_OPEN"]->loadFromFile("Resources/Sound Effects/door_lock.wav");
	this->soundEffects["MELEE_SOUND"] = new sf::SoundBuffer;
	this->soundEffects["MELEE_SOUND"]->loadFromFile("Resources/Sound Effects/melee.wav");
	
	this->meleeSound.setBuffer(*this->soundEffects["MELEE_SOUND"]);
	this->meleeSound.setVolume(10.f);
	this->pickUpCoinSound.setBuffer(*this->soundEffects["PICKUP_COIN"]);
	this->pickUpCoinSound.setVolume(10.f);
	this->pickUpPooSound.setBuffer(*this->soundEffects["PICKUP_POO"]);
	this->pickUpPooSound.setVolume(10.f);
	this->pickUpChickenSound.setBuffer(*this->soundEffects["PICKUP_CHICKEN"]);
	this->pickUpChickenSound.setVolume(10.f);
	this->pickUpHealthSound.setBuffer(*this->soundEffects["PICKUP_HEALTH"]);
	this->pickUpHealthSound.setVolume(10.f);
	this->openDoorSound.setBuffer(*this->soundEffects["DOOR_OPEN"]);
	this->openDoorSound.setVolume(15.f);
}

void GameState2::initTexture()
{
	this->textures["BULLET"] = new sf::Texture;
	this->textures["BULLET"]->loadFromFile("Texture/bullet.png");
	this->textures["FLIPPED_BULLET"] = new sf::Texture;
	this->textures["FLIPPED_BULLET"]->loadFromFile("Texture/flipped_bullet.png");
	this->textures["SNIPER"] = new sf::Texture;
	this->textures["SNIPER"]->loadFromFile("Texture/Enemy/sniper.png");
	this->textures["HEALTH"] = new sf::Texture;
	this->textures["HEALTH"]->loadFromFile("Texture/Item/healthPack.png");
	this->textures["COIN"] = new sf::Texture;
	this->textures["COIN"]->loadFromFile("Texture/Item/coin.png");
	this->textures["POO"] = new sf::Texture;
	this->textures["POO"]->loadFromFile("Texture/Item/poo.png");
	this->textures["CHICKEN"] = new sf::Texture;
	this->textures["CHICKEN"]->loadFromFile("Texture/Item/chicken.png");
	this->textures["KEY"] = new sf::Texture;
	this->textures["KEY"]->loadFromFile("Texture/Item/key.png");
}

void GameState2::initPlayer()
{
	this->player->setPosition(0, 300);
	//this->player->setScale(3, 3);
	this->player->createHitbox(25.f, 10.f, 55.f, 90.f);
	this->player->setJumpForce(450.f);
}

void GameState2::initEnemy()
{
	this->enemies.push_back(new Enemy(this->textures["SNIPER"], "SNIPER", 2348.f, 477.f));
	this->enemies.push_back(new Enemy(this->textures["SNIPER"], "SNIPER", 88.f, 2045.f));
	this->enemies.push_back(new Enemy(this->textures["SNIPER"], "SNIPER", 347.f, 2040.f));
	this->enemies.push_back(new Enemy(this->textures["SNIPER"], "SNIPER", 3131.f, 2096.f));
	this->enemies.push_back(new Enemy(this->textures["SNIPER"], "SNIPER", 4627.f, 1199.f));
	this->enemies.push_back(new Enemy(this->textures["SNIPER"], "SNIPER", 3149.f, 1199.f));
	this->enemies.push_back(new Enemy(this->textures["SNIPER"], "SNIPER", 6436.f, 545.f));
	this->enemies.push_back(new Enemy(this->textures["SNIPER"], "SNIPER", 5883.f, 542.f));
	this->enemies.push_back(new Enemy(this->textures["SNIPER"], "SNIPER", 12104.f, 2049.f));
	this->enemies.push_back(new Enemy(this->textures["SNIPER"], "SNIPER", 11863.f, 2044.f));
	this->enemies.push_back(new Enemy(this->textures["SNIPER"], "SNIPER", 6550.f, 2119.f));
	this->enemies.push_back(new Enemy(this->textures["SNIPER"], "SNIPER", 6703.f, 2119.f));
	this->enemies.push_back(new Enemy(this->textures["SNIPER"], "SNIPER", 9850.f, 2100.f));
	this->enemies.push_back(new Enemy(this->textures["SNIPER"], "SNIPER", 4722.f, 2091.f));
	this->enemies.push_back(new Enemy(this->textures["SNIPER"], "SNIPER", 9950.f, 485.f));
	this->enemies.push_back(new Enemy(this->textures["SNIPER"], "SNIPER", 11854.f, 485.f));
	this->enemies.push_back(new Enemy(this->textures["SNIPER"], "SNIPER", 11484.f, 485.f));
	this->enemies.push_back(new Enemy(this->textures["SNIPER"], "SNIPER", 2708.f, 1196.f));
	this->enemies.push_back(new Enemy(this->textures["SNIPER"], "SNIPER", 9679.f, 1195.f));
}

void GameState2::initItem()
{
	this->items.push_back(new Item(this->textures["COIN"], "COIN", 100, 1840));
	this->items.push_back(new Item(this->textures["COIN"], "COIN", 1040, 1073));
	this->items.push_back(new Item(this->textures["COIN"], "COIN", 550, 320));
	this->items.push_back(new Item(this->textures["COIN"], "COIN", 590, 320));
	this->items.push_back(new Item(this->textures["COIN"], "COIN", 630, 320));
	this->items.push_back(new Item(this->textures["COIN"], "COIN", 1505, 849));
	this->items.push_back(new Item(this->textures["COIN"], "COIN", 1505, 537));
	this->items.push_back(new Item(this->textures["COIN"], "COIN", 3500, 150));
	this->items.push_back(new Item(this->textures["COIN"], "COIN", 1505, 1363));
	this->items.push_back(new Item(this->textures["COIN"], "COIN", 1505, 1748));
	this->items.push_back(new Item(this->textures["COIN"], "COIN", 3800, 1384));
	this->items.push_back(new Item(this->textures["COIN"], "COIN", 3800, 1607));
	this->items.push_back(new Item(this->textures["COIN"], "COIN", 3800, 1804));
	this->items.push_back(new Item(this->textures["COIN"], "COIN", 7703, 693));
	this->items.push_back(new Item(this->textures["COIN"], "COIN", 7703, 1499));
	this->items.push_back(new Item(this->textures["COIN"], "COIN", 8717, 100));
	this->items.push_back(new Item(this->textures["COIN"], "COIN", 11140, 1040));
	this->items.push_back(new Item(this->textures["COIN"], "COIN", 10706, 1868));
	this->items.push_back(new Item(this->textures["COIN"], "COIN", 10706, 1568));
	this->items.push_back(new Item(this->textures["COIN"], "COIN", 10706, 1268));
	this->items.push_back(new Item(this->textures["COIN"], "COIN", 10706, 968));
	this->items.push_back(new Item(this->textures["COIN"], "COIN", 10706, 668));
	this->items.push_back(new Item(this->textures["COIN"], "COIN", 10706, 368));
	this->items.push_back(new Item(this->textures["POO"], "POO", 1410, 2135));
	this->items.push_back(new Item(this->textures["POO"], "POO", 1460, 2135));
	this->items.push_back(new Item(this->textures["POO"], "POO", 1510, 2135));
	this->items.push_back(new Item(this->textures["POO"], "POO", 1560, 2135));
	this->items.push_back(new Item(this->textures["POO"], "POO", 1610, 2135));
	this->items.push_back(new Item(this->textures["POO"], "POO", 7686, 2193));
	this->items.push_back(new Item(this->textures["CHICKEN"], "CHICKEN", 3647, 295));
	this->items.push_back(new Item(this->textures["CHICKEN"], "CHICKEN", 11702, 1835));
	this->items.push_back(new Item(this->textures["CHICKEN"], "CHICKEN", 6632, 2020));




	this->items.push_back(new Item(this->textures["KEY"], "KEY", 5655, 1983));
}

void GameState2::initView()
{
	this->view = new sf::View;
	this->viewPos.x = this->window->getSize().x / 2;
	this->viewPos.y = this->window->getSize().y / 2;
	this->view->setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));
	this->currentCamera = this->window->getSize().x - 50.f;
	this->moveCamera = false;
	this->nextViewPos = viewPos.x;
}

void GameState2::initGUI()
{
	this->hpBar.setPosition(10.f, 35.f);
	this->hpBar.setSize(sf::Vector2f(10.f * this->player->getHp(), 20.f));
	this->hpBar.setFillColor(sf::Color::Red);

	this->hpBarOutline.setPosition(10.f, 35.f);
	this->hpBarOutline.setSize(sf::Vector2f(10.f * this->player->getMaxHp(), 20.f));
	this->hpBarOutline.setOutlineThickness(2.f);
	this->hpBarOutline.setOutlineColor(sf::Color::Black);
	this->hpBarOutline.setFillColor(sf::Color::Transparent);

	this->BonusItemIcon.setTexture(this->textures["BONUS"]);
	this->BonusItemIcon.setSize(sf::Vector2f(30.f, 30.f));
	this->BonusItemIcon.setPosition(20.f, 60.f);

	if (!this->scoreFont.loadFromFile("Fonts/04font.ttf"))
		std::cout << "ERROR::GAME_STATE::COULD NOT LOAD SCOREFONT FROM FILE" << std::endl;
	this->scoreText.setFont(this->scoreFont);
	this->scoreText.setString(std::to_string(this->player->getScore()));
	this->scoreText.setCharacterSize(30.f);
	this->scoreText.setFillColor(sf::Color(250, 220, 0, 250));
	this->scoreText.setOutlineThickness(2.f);
	this->scoreText.setOutlineColor(sf::Color::Black);
	this->scoreText.setPosition(this->view->getCenter().x + this->window->getSize().x / 2.f - this->scoreText.getGlobalBounds().width - 20.f, 10.f);

	this->playerName.setFont(this->scoreFont);
	this->playerName.setString(this->player->getName());
	this->playerName.setCharacterSize(20.f);
	this->playerName.setFillColor(sf::Color(255, 255, 255, 255));
	this->playerName.setOutlineThickness(2.f);
	this->playerName.setOutlineColor(sf::Color::Black);
	this->playerName.setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f + this->playerName.getGlobalBounds().width + 10.f, 5.f);

}


GameState2::GameState2(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::View* view, Player* player)
	: State(window, supportedKeys, states, view, player)
{
	this->initTexture();
	this->initVariables();
	this->initPlayer();
	this->initEnemy();
	this->initMusic();
	this->initSoundEffects();
	this->initPlatform();
	this->initKeybinds();
	this->initBackground();
	this->initItem();
	this->initView();
	this->initGUI();

	this->createTextHolder(this->view->getCenter().x - this->window->getSize().x / 2.f + 5 , this->view->getCenter().y + this->window->getSize().y / 2.f - 200, 
						this->window->getSize().x - 10, 190.f, "FIND A KEY! TO PROCEED THE MISSION");
}

GameState2::~GameState2()
{
	//delete textures
	for (auto& i : this->textures)
	{
		delete i.second;
	}
	//delete bullets
	for (auto* bullet : this->bullets)
	{
		delete bullet;
	}
	//delete platforms
	for (auto* platform : this->platforms)
	{
		delete platform;
	}
	//delete Enemies
	for (auto* enemy : this->enemies)
	{
		delete enemy;
	}
	//delete Items
	for (auto* item : this->items)
	{
		delete item;
	}
	//delete Sound Effects
	for (auto& i : this->soundEffects)
	{
		delete i.second;
	}
	//delete Text
	for (auto* text : this->textHolder)
	{
		delete text;
	}
}

void GameState2::endState()
{
	std::cout << "Ending State2" << std::endl;
}

void GameState2::spawnEnemies()
{
}

void GameState2::createTextHolder(float pos_x, float pos_y, float sizeX, float sizeY, sf::String text)
{
	this->textHolder.push_back(new TextHolder(pos_x, pos_y, sizeX, sizeY, text));
}

void GameState2::updateViewPosition()
{
	this->view->setCenter(this->player->getPosition().x, this->player->getPosition().y);
	/*else if (this->player->getPosition().x > this->backgroundTexture.getSize().x - this->window->getSize().x / 2.f)
	{
		this->view->setCenter(this->backgroundTexture.getSize().x - this->window->getSize().x / 2.f, this->window->getSize().y / 2.f);
	}*/
	/*if (this->player->getPosition().y > this->window->getSize().y / 2.f + 200.f)
	{
		this->view->setCenter(this->player->getPosition().x, this->player->getPosition().y);
	}
	else
		this->view->setCenter(this->player->getPosition().x, this->window->getSize().y / 2.f);*/

}

void GameState2::updateInput(const float& dt)
{
	this->checkForQuit();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && this->player->getIsJump() == false)
	{
		if (this->shootTimer.getElapsedTime().asSeconds() >= this->player->getShootCD())
		{
			if (this->player->getIsFaceRight())
				this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPosition().x + this->player->getGlobalBounds().width, this->player->getPosition().y + this->player->getGlobalBounds().height / 2.f - 20.f, 1.f, 0.f, 10.f));
			else
				this->bullets.push_back(new Bullet(this->textures["FLIPPED_BULLET"], this->player->getPosition().x, this->player->getPosition().y + this->player->getGlobalBounds().height / 2.f - 20.f, -1.f, 0.f, 10.f));
			this->shootTimer.restart();
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::End))
	{
		this->bg_music.stop();
		this->states->pop();
		this->states->push(new BossFightState(this->window, this->supportedKeys, this->states, this->view, this->player));
	}
}

void GameState2::updatePlayer(const float& dt)
{
	this->player->update(dt);
}

void GameState2::updateEnemy(const float& dt)
{
	int temp = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update(this->player, dt);
		if (enemy->getHp() <= 0)
		{
			if (enemy->getIsDeath())
			{
				delete this->enemies.at(temp);
				this->enemies.erase(this->enemies.begin() + temp);
				temp--;
			}
		}
		temp++;
	}
}

void GameState2::updateCollision(const float& dt)
{
	//Check collision between the left side of the WINDOW
	if (this->player->getPosition().x < 0.f)
	{
		this->player->setPosition(0.f, this->player->getPosition().y);
	}
	//Check collision between player and the end of the map
	if (this->player->getPosition().x + this->player->getGlobalBounds().width >= this->backgroundTexture.getSize().x * 4.f)
	{
		this->player->setPosition(this->backgroundTexture.getSize().x - this->player->getGlobalBounds().width, this->player->getPosition().y);
	}
	if (this->player->getPosition().y < 0)
	{
		this->player->setPosition(this->player->getPosition().x, 0.f);
	}
	//Check collision between the PLAYER and PLATFORMS
	unsigned counter = 0;
	for (int i = 0; i < this->platforms.size(); i++)
	{
		Platform* platform = this->platforms[i];
		if (platform->getType() == "stairL" || platform->getType() == "stairR")
		{
			if (platform->getCollider().checkCollision(this->player->getCollider(), this->player->getSprite(), this->direction, 1.f, platform->getType()))
			{
				this->player->onCollision(this->direction, dt);
				this->player->resetVelocityY();
			}
		}
		else if (platform->getType() == "door")
		{
			if (platform->getGlobalBounds().intersects(this->player->getGlobalBounds()))
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->haveKey)
				{
					this->openDoorSound.play();
					this->bg_music.stop();
					this->states->pop();
					this->states->push(new BossFightState(this->window, this->supportedKeys, this->states, this->view, this->player));
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !this->haveKey && !this->isPressed)
				{
					this->createTextHolder(this->view->getCenter().x - this->window->getSize().x / 2.f + 5, this->view->getCenter().y + this->window->getSize().y / 2.f - 200, this->window->getSize().x - 10.f, 190.f, "* THE DOOR IS LOCK!");
					this->textTimer.restart();
					this->isPressed = true;
				}
			}
		}
		else if (platform->getCollider().checkCollision(this->player->getCollider(), this->player->getSprite(), this->direction, 1.f))
		{
			this->player->onCollision(this->direction, dt);
			this->player->resetVelocityY();
		}
		else
		{
			this->player->setOnGround(0);
		}
		for (auto* bullet : this->bullets)
		{
			//PLAYER'S BULLETS collide with PLATFORMS
			if (platform->getBody().getGlobalBounds().intersects(bullet->getBounds()))
			{
				delete this->bullets.at(counter);
				this->bullets.erase(this->bullets.begin() + counter);
				--counter;
			}
		}
	}
	counter++;
	//Check the collision between PLAYER and ENEMIES
	for (auto* enemy : this->enemies)
	{
		if (this->player->getGlobalBounds().intersects(enemy->getGlobalBounds()) && enemy->getHp() > 0)
		{
			if (this->meleeCooldown.getElapsedTime().asSeconds() >= 3.f)
			{
				this->player->Melee();
				this->meleeSound.play();
				this->meleeCooldown.restart();
				enemy->takeDmg(3);
				if (enemy->getHp() <= 0)
				{
					this->player->addScore(enemy->getPoint());
				}
			}
		}
	}
}

void GameState2::updateItemsCollision(const float& dt)
{
	unsigned itemCounter = 0;
	for (auto* item : this->items)
	{
		item->update(dt);
		if (item->getGlobalBounds().intersects(this->player->getGlobalBounds()) && this->player->getHp() < this->player->getMaxHp() && item->getType() == "HEAL")
		{
			delete this->items.at(itemCounter);
			this->player->heal(1);
			this->items.erase(this->items.begin() + itemCounter);
			this->pickUpHealthSound.play();
			--itemCounter;
		}
		if (item->getGlobalBounds().intersects(this->player->getGlobalBounds()) && item->getType() == "COIN")
		{
			delete this->items.at(itemCounter);
			this->player->addScore(2.f);
			this->items.erase(this->items.begin() + itemCounter);
			this->pickUpCoinSound.play();
			--itemCounter;
		}
		if (item->getGlobalBounds().intersects(this->player->getGlobalBounds()) && item->getType() == "POO")
		{
			delete this->items.at(itemCounter);
			this->player->takeDmg(5);
			this->items.erase(this->items.begin() + itemCounter);
			this->pickUpPooSound.play();
			--itemCounter;
		}
		if (item->getGlobalBounds().intersects(this->player->getGlobalBounds()) && item->getType() == "CHICKEN")
		{
			delete this->items.at(itemCounter);
			this->player->addScore(10);
			this->player->heal(5);
			this->items.erase(this->items.begin() + itemCounter);
			this->pickUpChickenSound.play();
			--itemCounter;
		}
		if (item->getGlobalBounds().intersects(this->player->getGlobalBounds()) && item->getType() == "KEY")
		{
			delete this->items.at(itemCounter);
			this->haveKey = true;
			this->items.erase(this->items.begin() + itemCounter);
			this->pickUpCoinSound.play();
			this->KeySprite.setTexture(*this->textures["KEY"]);
			this->createTextHolder(this->view->getCenter().x - this->window->getSize().x / 2.f + 5, this->view->getCenter().y + this->window->getSize().y / 2.f - 200, this->window->getSize().x - 10.f, 190.f, "YOU HAVE FOUND A KEY!\n* NOW YOU NEED TO FIND A DOOR!");
			this->textTimer.restart();
			this->KeySprite.setTextureRect({ 0, 0, 14, 21 });
			--itemCounter;
		}
		++itemCounter;
	}
}

void GameState2::updateBullet(const float& dt)
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		//bullet culling (right screen)
		if (bullet->getBounds().left + bullet->getBounds().width > this->view->getCenter().x + this->window->getSize().x / 2.f)
		{
			//delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
			//std::cout << this->bullets.size() << std::endl;
		}
		//bullet culling (left screen)
		if (bullet->getBounds().left < this->view->getCenter().x - this->window->getSize().x / 2.f - 50)
		{
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
			//std::cout << this->bullets.size() << std::endl;
		}
		//check if bullet hit the enemy(ies)
		for (auto* enemy : this->enemies)
		{
			if (bullet->getBounds().intersects(enemy->getGlobalBounds()) && enemy->getHp() > 0)
			{
				std::cout << enemy->getHp() << std::endl;
				enemy->takeDmg(1);
				////if enemy's hp is 0
				if (enemy->getHp() == 0)
				{
					this->player->addScore(enemy->getPoint());
					if (enemy->getIsDrop())
						this->items.push_back(new Item(this->textures["HEALTH"], "HEAL", enemy->getPosition().x, enemy->getPosition().y + enemy->getGlobalBounds().height - 40.f));
				}
				delete this->bullets.at(counter);
				this->bullets.erase(this->bullets.begin() + counter);
				--counter;
			}
			//temp++;
		}
	}
	++counter;
}

void GameState2::updateGUI(const float& dt)
{
	if (this->player->getHp() > 20)
		this->player->setHP(this->player->getMaxHp());
	this->hpBarOutline.setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f + 10.f, this->view->getCenter().y - this->window->getSize().y / 2.f + 35.f);
	this->hpBar.setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f + 10.f, this->view->getCenter().y - this->window->getSize().y / 2.f + 35.f);
	this->hpBar.setSize(sf::Vector2f(this->player->getHp() * 10.f, 20.f));

	this->BonusItemIcon.setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f + 20.f, this->view->getCenter().y - this->window->getSize().y / 2.f + 60.f);
	this->BonusItemIcon.setFillColor(sf::Color(255, 255, 255, this->changeColor -= 500 * dt));

	this->scoreText.setString(std::to_string(this->player->getScore()));
	this->scoreText.setPosition(this->view->getCenter().x + this->window->getSize().x / 2.f - this->scoreText.getGlobalBounds().width - 20.f, this->view->getCenter().y - this->window->getSize().y / 2.f + 10.f);

	this->playerName.setString(this->player->getName());
	this->playerName.setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f + 10.f, this->view->getCenter().y - this->window->getSize().y / 2.f + 5.f);

	this->KeySprite.setScale(1.5f, 1.5f);
	this->KeySprite.setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f + 20.f, this->view->getCenter().y - this->window->getSize().y / 2.f + 60.f);

	for (auto* text : this->textHolder)
	{
		text->update(dt);
		text->setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f + 5, this->view->getCenter().y + this->window->getSize().y / 2.f - 200);
	}
	if (this->textTimer.getElapsedTime().asSeconds() >= 4.f)
	{
		this->textHolder.clear();
		this->isPressed = false;
	}
}

void GameState2::update(const float& dt)
{
	while (this->window->pollEvent(this->ev))
	{

	}

	this->updateViewPosition();

	this->spawnEnemies();

	this->window->setView(*this->view);
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateCollision(dt);
	this->updateItemsCollision(dt);
	this->updateBullet(dt);
	this->updatePlayer(dt);
	this->updateEnemy(dt);


	this->updateGUI(dt);

	//this->view->setCenter(this->viewPos);

	if (this->player->getHp() <= 0)
	{
		this->states->pop();
		this->states->push(new GameOverState(this->window, this->supportedKeys, this->states, this->view, this->player));
		this->bg_music.stop();
	}
	
}

void GameState2::renderPlayer()
{
	this->player->render(this->window);
}

void GameState2::renderGUI()
{
	this->window->draw(this->hpBar);
	this->window->draw(this->hpBarOutline);

	if (this->player->getBonusState())
		this->window->draw(this->BonusItemIcon);
	else this->changeColor = 255;

	this->window->draw(this->scoreText);
	this->window->draw(this->playerName);

	this->window->draw(this->KeySprite);

	for (auto* text : this->textHolder)
	{
		if (this->textTimer.getElapsedTime().asSeconds() <= 4.f)
		{
			text->render(this->window);
		}
	}
}

void GameState2::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	//render
	/*for (int i = 0; i < this->platforms.size(); i++)
	{
		Platform* platform = this->platforms[i];
		platform->render(this->window);
	}*/

	this->window->draw(this->background);

	for (auto* item : this->items)
	{
		item->render(this->window);
	}

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	this->renderPlayer();

	this->renderGUI();
}
