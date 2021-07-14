#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <map>

#include "maze.h"
#include "priority_queue.h"

struct AStarCombo
{
    int index;
    int fScore;
    bool operator== (const AStarCombo& asc) const;
    bool operator< (const AStarCombo& asc) const;
    bool operator> (const AStarCombo& asc) const;
};

class AStar
{
public:

    AStar(Maze* maze, int start, int goal);

    enum RESULT
    {
        NO_PATH,
        CONTINUE,
        FINISHED
    };

    enum ASTAR_PART
    {
        CURRENT_PATH = Maze::LAST_PART+1,
        VISITED,
    };

    void setStart(int start);
    void setGoal(int goal);
    std::vector<int> getCurrentPath() const;
    int calculate();
private:
    int getHeuristic(int current, int goal) const;

    AStarCombo m_current;
    int m_start;
    int m_goal;

    PrioQueue<AStarCombo> prio;
    std::map<int,int> cameFrom;
    std::map<int,int> gScore;
    std::map<int,int> fScore;
    Maze* m_maze;
};

#endif
