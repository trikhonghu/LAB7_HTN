/*
 * leaderboard.h
 *
 *  Created on: Dec 28, 2023
 *      Author: Windows
 */

#ifndef INC_LEADERBOARD_H_
#define INC_LEADERBOARD_H_

#include "main.h"

struct player{
	int player_ID;
	int player_score;
	int player_mode;
	struct player *next;
};

void addPlayer(struct player **head, int ID, int score, int mode);
//{
//    struct player *newPlayer = (struct player *)malloc(sizeof(struct player));
//    if (newPlayer == NULL) {
//        return;
//    }
//    newPlayer->player_ID = ID;
//    newPlayer->player_score = score;
//    newPlayer->next = NULL;
//
//    if (*head == NULL || score > (*head)->player_score) {
//        newPlayer->next = *head;
//        *head = newPlayer;
//    } else {
//        struct player *current = *head;
//        while (current->next != NULL && score <= current->next->player_score) {
//            current = current->next;
//        }
//        newPlayer->next = current->next;
//        current->next = newPlayer;
//    }
//}
//int comparePlayer(const void *a, const void *b){
//    const struct player *playerA = *(const struct player **)a;
//    const struct player *playerB = *(const struct player **)b;
//    return (playerB->player_score - playerA->player_score);
//}

#endif /* INC_LEADERBOARD_H_ */
