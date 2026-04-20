#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const int MAX_AGENTS = 10000;

typedef struct Agent {
    float money;
    float goods;
    float production_rate;

} Agent;

static void agents_init(Agent agents[])
{
    assert(agents);

    for (int i = 0; i < MAX_AGENTS; i++) {
        agents[i].money = rand() % 100 + 50;                  // 50 - 149
        agents[i].goods = rand() % 50;                        // 0 - 49
        agents[i].production_rate = (rand() % 10 + 1) / 2.0f; // 0.5 - 5
    }
}

static void produce(Agent agents[])
{
    assert(agents);

    for (int i = 0; i < MAX_AGENTS; i++) {
        agents[i].goods += agents[i].production_rate;
    }
}

static void consume(Agent agents[])
{
    assert(agents);

    for (int i = 0; i < MAX_AGENTS; i++) {
        const float consumption = 2.0f;

        agents[i].goods = fmaxf(agents[i].goods - consumption, 0);
    }
}

static float calculate_price(Agent agents[])
{
    assert(agents);

    float total_goods = 0;
    float total_money = 0;

    for (int i = 0; i < MAX_AGENTS; i++) {
        total_goods += agents[i].goods;
        total_money += agents[i].money;
    }

    if (total_goods == 0)
        return 1.0f;

    return total_money / total_goods;
}

static void trade(Agent agents[], const float price)
{
    assert(agents);

    for (int i = 0; i < MAX_AGENTS; i++) {
        if (agents[i].goods < 5 && agents[i].money > price) {
            const int seller = rand() % MAX_AGENTS;

            if (agents[seller].goods > 5) {
                agents[i].goods++;
                agents[i].money -= price;

                agents[seller].goods--;
                agents[seller].money += price;
            }
        }
    }
}

static void print_stats(const Agent agents[], const int step, const float price)
{
    float total_money = 0;
    float total_goods = 0;

    for (int i = 0; i < MAX_AGENTS; i++) {
        total_money += agents[i].money;
        total_goods += agents[i].goods;
    }

    printf("Steps: %d\n", step);
    printf("Price: %.2f\n", price);
    printf("Total Money: %.2f\n", total_money);
    printf("Total Goods: %.2f\n", total_goods);
    printf("\n-------------------------------------\n");
}

int main(void)
{
    srand(time(NULL));

    Agent agents[MAX_AGENTS];
    agents_init(agents);

    for (int step = 0; step < 100; step++) {
        produce(agents);
        consume(agents);

        const float price = calculate_price(agents);
        trade(agents, price);

        print_stats(agents, step, price);
    }

    return 0;
}
