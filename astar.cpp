#include "astar.h"
#include "maze.h"

AStar::AStar(Maze* maze, int start, int goal)
    : m_start(start), m_goal(goal), m_maze(maze)
{
    prio = PrioQueue<AStarCombo>();
    prio.add({start, getHeuristic(start, goal)});

    gScore[start] = 0;
    fScore[start] = getHeuristic(start, goal);
}

void AStar::setStart(int start)
{
    m_start = start;
}

void AStar::setGoal(int goal)
{
    m_goal = goal;
}

int AStar::getHeuristic(int current, int goal) const
{
    // current  = x1 * columns() + y1
    // goal     = x2 * columns() + y2

    int length = 0;
    // difference in columns
    length += (goal-current) % m_maze->columns();
    // difference in rows
    length += (goal-current) / m_maze->rows();
    // add one more to reach goal
    length++;
    return length;
}

path AStar::getCurrentPath() const
{
    path resultPath;
    resultPath.push_back(m_current.index);

    auto result = cameFrom.find(m_current.index);
    while (result != cameFrom.end()) {
        resultPath.push_back(result->second);
        result = cameFrom.find(result->second);
    }

    std::reverse(resultPath.begin(), resultPath.end());
    return resultPath;
}

int AStar::calculate()
{
    if (!prio.isEmpty() && m_current.index != m_goal) {

        m_current = prio.pop();

        if (m_maze->position(m_current.index) == Maze::WALL)
            return CONTINUE;

        if (m_current.index == m_goal)
            return FINISHED;

        for (int neighbor: m_maze->getNeighbors(m_current.index)) {

            if (gScore.find(neighbor) == gScore.end())
                gScore[neighbor] = std::numeric_limits<int>::max();
            if (fScore.find(neighbor) == fScore.end())
                fScore[neighbor] = std::numeric_limits<int>::max();

            int temp_gScore = gScore[m_current.index] + m_maze->getCost(m_current.index, neighbor);

            if (temp_gScore < gScore[neighbor]) {

                cameFrom[neighbor] = m_current.index;
                gScore[neighbor] = temp_gScore;
                fScore[neighbor] = temp_gScore + getHeuristic(neighbor, m_goal);

                if (!prio.contains({neighbor,0})) {
                    prio.add({neighbor,fScore[neighbor]});
                }
            }
        }
        return CONTINUE;

    } else if (m_current.index == m_goal)
        return FINISHED;
    else
        return NO_PATH;
}

bool AStarCombo::operator==(const AStarCombo &asc) const
{
    if (index == asc.index)
        return true;
    return false;
}

bool AStarCombo::operator<(const AStarCombo &asc) const
{
    if(fScore < asc.fScore)
        return true;
    return false;
}

bool AStarCombo::operator>(const AStarCombo &asc) const
{
    if(fScore >= asc.fScore)
        return true;
    return false;
}
