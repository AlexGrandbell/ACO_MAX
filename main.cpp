#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>

using namespace std;

class ACO{
public:
    //蚂蚁类
    class Ant {
    public:
        int position; //当前蚂蚁的位置
        Ant() : position(0) {}
    };

    int pSize; //蚂蚁数量
    int maxGen;  //最大迭代次数
    double eRate; //信息素蒸发率
    double pheromoneInit; //初始信息素强度
    vector<double> pheromone; //信息素数组

    ACO(): pSize(10), maxGen(100), eRate(0.01), pheromoneInit(1.0){
        pheromone.resize(32, pheromoneInit);
    }

    int fitness(int x) {
        return x * x; //适应度函数 y = x^2
    }

    void updatePheromone(int bestPosition) {
        //更新信息素
        pheromone[bestPosition] += 1.0 / fitness(bestPosition); //在找到最佳位置时增加信息素
        for (int i = 0; i < pheromone.size(); ++i) {
            pheromone[i] *= (1.0 - eRate); //信息素蒸发
        }
    }

    int selectPosition() {
        //选择位置
        double totalPheromone = 0.0;
        for (int i = 0; i < pheromone.size(); ++i) {
            totalPheromone += pheromone[i];
        }

        double randVal = ((double)rand() / RAND_MAX) * totalPheromone;
        for (int i = 0; i < pheromone.size(); ++i) {
            randVal -= pheromone[i];
            if (randVal <= 0) {
                return i; //返回选择的位置
            }
        }
        return 0; //防止异常，返回 0
    }

    int run() {
        for (int i = 0; i < maxGen; ++i) {
            int bestPosition = 0;
            int bestFitness = 0;

            for (int j = 0; j < pSize; ++j) {
                Ant ant;
                ant.position = selectPosition(); //随机选择位置
                int currentFitness = fitness(ant.position);

                //寻找当前蚂蚁的最佳位置
                if (currentFitness > bestFitness) {
                    bestFitness = currentFitness;
                    bestPosition = ant.position;
                }
            }

            updatePheromone(bestPosition); //更新信息素
        }
        return max_element(pheromone.begin(), pheromone.end()) - pheromone.begin(); //找到最佳位置
    }

    void aco_run(){
        srand(time(0)); //设置随机数种子
        cout << "蚁群算法" << endl;

        //输入算法参数
//        cout << "输入蚁群大小、最大迭代次数、信息素蒸发率、初始信息素强度：" << endl;
//        cin >> pSize >> maxGen >> eRate >> pheromoneInit;

        cout << "函数最大值：" << fitness(run()) << endl; //输出最大值（y = x^2 的值）
    }
};

int main() {
    ACO aco;
    aco.aco_run();
    return 0;
}