#include "AIManager.h"
#include "GameSignals.h"
#include <iostream>
using std::cout;
using std::endl;

AIManager::AIManager(sf::Clock& _gameclock) : gameclock(_gameclock) {
	Signals::DistributeLinesLocally.connect(&AIManager::distributeLines, this);
	Signals::AmountAI.connect(&AIManager::setAmount, this);
	Signals::SpeedAI.connect(&AIManager::setSpeed, this);
}

void AIManager::setAmount(uint8_t amount) {
	if (amount > 20)
		return;
	static uint16_t id_count = 60000;
	while (bots.size() < amount) {
		if (botsCache.empty())
			bots.emplace_back(Signals::AddField(id_count, "AI" + std::to_string(id_count)), gameclock);
		else {
			bots.splice(bots.end(), botsCache, botsCache.begin());
			bots.back().setField(Signals::AddField(id_count, "AI" + std::to_string(id_count)));
		}
		bots.back().startAI();
		bots.back().id = id_count;
		id_count++;
		if (id_count < 60000)
			id_count = 60000;
	}

	while (bots.size() > amount) {
		Signals::RemoveField(bots.front().id);
		botsCache.splice(botsCache.end(), bots, bots.begin());
	}

	resetScore();
}

void AIManager::setSpeed(uint16_t speed) {
	for (auto& bot : bots)
		bot.setSpeed(speed);
}

bool AIManager::update(const sf::Time& t) {
	if (bots.empty())
		return false;

	for (auto& bot : bots)
		if (bot.alive) {
			bot.delayCheck(t);
			if (bot.playAI()) {
				bot.endRound(t, false);
				bot.score += bots.size() - alive;
				alive--;
			}
		}

	if (!alive)
		return true;

	return false;
}

void AIManager::startCountdown() {
	for (auto& bot : bots)
		bot.startCountdown();
}

void AIManager::countDown(int count) {
	for (auto& bot : bots)
		bot.countDown(count);
}

void AIManager::startRound() {
	for (auto& bot : bots)
		bot.startRound();

	alive = bots.size();
	terminateThread = false;
	if (alive)
		aiThread = std::thread(&AIManager::aiThreadRun, this);
	playersIncomingLines=0;
}

void AIManager::aiThreadRun() {
	while (true) {
		for (auto& bot : bots) {
			if (terminateThread)
				return;
			if (bot.alive)
				bot.aiThreadRun();
		}
		if (bots.front().nextmoveTime > gameclock.getElapsedTime())
			sf::sleep(sf::seconds(0));
	}
}

void AIManager::endRound(const sf::Time& t) {
	for (auto& bot : bots)
		if (bot.alive) {
			bot.endRound(t, true);
			bot.score += bots.size() + 1 - alive;
		}
	terminateThread = true;
	if (aiThread.joinable())
		aiThread.join();
}

void AIManager::distributeLines(int id, int lines) {
	if (!alive)
		return;
	float amount = lines / static_cast<float>(alive);

	for (auto& bot : bots)
		if (bot.alive && bot.id != id) {
			bot.incomingLines += amount;
			if (bot.incomingLines >= 1) {
				int rounded = bot.incomingLines;
				bot.addGarbage(rounded, bot.gameclock.getElapsedTime());
				bot.incomingLines -= rounded;
			}
		}

	if (id != 0) {
		playersIncomingLines += amount;
		if (playersIncomingLines >= 1) {
			int rounded = playersIncomingLines;
			Signals::AddGarbage(rounded);
			playersIncomingLines -= rounded;
		}
	}
}

bool AIManager::empty() {
	return bots.empty();
}

void AIManager::resetScore() {
	for (auto& bot : bots)
		bot.score = 0;
	playerScore = 0;
}

void AIManager::setScore(GameplayData & data) {
	playerScore += bots.size() - alive;

	using sPair = std::pair<uint16_t, sf::Uint16>;

	std::vector<sPair> sorting;
	for (auto it = bots.begin(); it != bots.end(); it++)
		sorting.emplace_back(it->score, it->id);

	sorting.emplace_back(playerScore, 200);

	std::sort(sorting.begin(), sorting.end(), [](sPair p1, sPair p2) { return p2.first < p1.first; });

	for (auto& pair : sorting) {
		if (pair.second == 200)
			Signals::AddLocalScore(data, pair.second, Signals::GetName(), playerScore);
		else for (auto it = bots.begin(); it != bots.end(); it++)
			if (it->id == pair.second) {
				Signals::AddLocalScore(it->data, it->id, it->field->text.name, it->score);
				break;
			}
	}
}