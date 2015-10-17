#include <stdio.h>
#include <string.h>

#include "game.h"
#include "klingon.h"

static int e_ = 10000;
static int t_ = 8;

void fireWeapon(char *command, char *parameter, struct Klingon *enemy) {
	if (streq(command, "phaser")) {
		int amount = atoi(parameter);
		if (e_ >= amount) {
			int distance = enemy->distance;
			if (distance > 4000) {
				printf("Klingon out of range of phasers at %d sectors...\n", distance);
			} else {
				int damage = amount - (((amount /20)* distance /200) + RND(200));
				if (damage < 1)
					damage = 1;
				printf("Phasers hit Klingon at %d sectors with %d units\n", distance, damage);
				if (damage < enemy->energy) {
					enemy->energy -= damage;

					printf("Klingon has %d remaining\n", enemy->energy);
				} else {
					printf("Klingon destroyed!\n");
					enemy->destroyed = 1;
				}
			}
			e_ -= amount;

		} else {
			printf("Insufficient energy to fire phasers!\n");
		}

	} else if (streq(command, "photon")) {
		if (t_ > 0) {
			int distance = enemy->distance;
			if ((RND(4) + ((distance / 500) + 1) > 7)) {
				printf("Torpedo missed Klingon at %d sectors...\n", distance);
			} else {
				int damage = 800 + RND(50);
				printf("Photons hit Klingon at %d sectors with %d units\n", distance, damage);

				if (damage < enemy->energy) {
					enemy->energy -= damage;
					printf("Klingon has %d remaining\n", enemy->energy);
				} else {
					printf("Klingon destroyed!\n");
					enemy->destroyed = 1;
				}
			}
			t_--;

		} else {
			printf("No more photon torpedoes!\n");
		}
	}
}
