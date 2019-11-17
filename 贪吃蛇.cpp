#include <vector>
#include <deque>
#include <random>
#include <ctime>
#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <functional>
#include <cctype>

class food
{
public:
	typedef std::pair<int, int> coordinate;
	void create();//生成食物
	coordinate get_location() const { return location; }//获取食物坐标
	food(int w, int h) :W(w), H(h) { create(); }

private:
	coordinate location;//食物坐标
	const int W;//最大生成宽度
	const int H;//最大生成高度
};

void food::create()
{
	std::default_random_engine e(static_cast<int>(time(0)));
	std::uniform_int_distribution<int> u_x(1, W), u_y(1, H);
	location = coordinate(u_x(e), u_y(e));
}

typedef food poisonousFruit;//毒果，其类定义与食物相同，但吃到会使蛇身长度-1

class snake
{
public:
	typedef std::pair<int, int> coordinate;
	snake();
	void move(char direction);//移动
	std::deque<coordinate> get_body() const{ return body; }//获取蛇身
	char get_last_direction() const { return last_direction; }//获取上次运动方向
	int get_length() const{ return body.size(); }//获取蛇长
	void remove_tail() { body.pop_back(); }//去除蛇尾

private:
	std::deque<coordinate> body;//蛇身
	char last_direction;//记录上次运动方向
	bool rectify(const int &direction);//修正方向
};

snake::snake()
{
	body.push_front(coordinate(1, 1));
	body.push_front(coordinate(2, 1));
	body.push_front(coordinate(3, 1));
	body.push_front(coordinate(4, 1));
	last_direction = 77;
}

void snake::move(char direction)
{
	if (rectify(direction))//如果蛇试图掉头，则运动方向不变（全路段禁止掉头！！）
		direction = last_direction;
	int head_x(body.begin()->first);
	int head_y(body.begin()->second);
	switch (direction)
	{
	case 80: body.push_front(coordinate(head_x, head_y + 1)); break;//down
	case 72: body.push_front(coordinate(head_x, head_y - 1)); break;//up
	case 75: body.push_front(coordinate(head_x - 1, head_y)); break;//left
	case 77: body.push_front(coordinate(head_x + 1, head_y)); break;//right
	default: direction = last_direction;
	}
	last_direction = direction;//更新数据
}

bool snake::rectify(const int &direction)
{
	if (direction == 72 && last_direction == 80)
		return true;
	else if (direction == 80 && last_direction == 72)
		return true;
	else if (direction == 77 && last_direction == 75)
		return true;
	else if (direction == 75 && last_direction == 77)
		return true;
	else
		return false;
}

class chessBoard
{
public:
	typedef std::pair<int, int> coordinate;//坐标
	chessBoard();
	virtual void startGame() = 0;
	virtual ~chessBoard() = default;

private:
	const int W = 18;//棋盘宽度
	const int H = 18;//棋盘高度

protected:
	std::vector<std::vector<char>> point_set;//棋盘的点集
	const int get_width() { return W; }//获取宽度
	const int get_height() { return H; }//获取长度
	void add_to_chessboard(const coordinate &co, const char &symbol);//将co所指坐标以符号symbol添加至棋盘
	void clear();//清空棋盘
	void print() const;//打印棋盘
	bool is_available(const coordinate &co) const;//判断该点是否为空

};

chessBoard::chessBoard() :point_set(H + 2, std::vector<char>(W + 2, ' '))
{
	for (int i = 0; i != W + 2; ++i)//载入边界
		for (int j = 0; j != H + 2; ++j)
			if (i == 0 || j == 0 || i == W + 1 || j == H + 1)
				point_set[i][j] = '#';
}

void chessBoard::print() const
{
	system("cls");//清屏
	for (int i = 0; i != H + 2; ++i)
	{
		for (int j = 0; j != W + 2; ++j)
			std::cout << point_set[i][j] << ' ';
		std::cout << std::endl;
	}
}

void chessBoard::add_to_chessboard(const coordinate &co, const char &symbol)
{
	try//检测是否越界
	{
		if (co.first > W || co.first < 1 || co.second > H || co.second < 1)
			throw std::range_error("Coordinate Transboundary!!");
		else
			point_set[co.second][co.first] = symbol;//载入符号
	}
	catch (std::range_error err)//越界处理
	{
		std::cerr << "\tError:" << err.what() << std::endl
			<< "\tPress any key to exit the game";
		system("pause > nul");
		exit(-1);
	}
}

void chessBoard::clear()
{
	for (int i = 1; i != H + 1; ++i)
		for (int j = 1; j != W + 1; ++j)
			if(point_set[i][j] != ' ')
				point_set[i][j] = ' ';
}

class snakeChessBoard: public chessBoard
{
public:
	virtual void startGame();
	snakeChessBoard() :food(get_width(), get_height()), poi(get_width(), get_height()) {};
	
private:
	food food;
	poisonousFruit poi;
	snake snake;
	const int gameSpeed = 400;//游戏速度
	bool judge();//规则判定

};

bool chessBoard::is_available(const coordinate &co) const
{
	return (point_set[co.second][co.first] == ' ');
}

void snakeChessBoard::startGame()
{
	do
	{
		clear();//清空棋盘
		auto snake_body = snake.get_body();//将蛇导入棋盘
		add_to_chessboard(*(snake_body.begin()), '@');
		for (auto snake_body_beg = snake_body.begin() + 1; snake_body_beg != snake_body.end(); ++snake_body_beg)
			add_to_chessboard(*snake_body_beg, '*');
		while (!is_available(food.get_location()))//将食物导入棋盘
				food.create();
		add_to_chessboard(food.get_location(), '$');
		while (!is_available(poi.get_location()))//将毒果导入棋盘
			poi.create();
		add_to_chessboard(poi.get_location(), '!');
		print();
		int start = clock();//获取当前时间
		char direction(snake.get_last_direction());
		while(clock() - start <= gameSpeed )
		{
			if (_kbhit() )
			{
				do //获取按键
				{
					direction = _getch();
				} while (!isascii(direction));
				if (direction != 72 && direction != 75 && direction != 77 && direction != 80)//如果输入非方向键，则沿原方向前进
					direction = snake.get_last_direction();
			}
		}
		snake.move(direction);//移动
	} while (judge());
	std::cout << "\n\n\n\tGame Over!!" << std::endl
		<< "\tYou have lost!!" << std::endl
		<< "\tPress any key to exit the game";
	system("pause >> nul");
	exit(0);
}

bool snakeChessBoard::judge()
{
	std::deque<coordinate> snake_body(snake.get_body());
	if (snake_body.begin()->first == 0 || snake_body.begin()->first == get_width() + 1 || snake_body.begin()->second == 0 || snake_body.begin()->second == get_height() + 1)//检测有无撞到墙壁
		return false;
	else if (std::find(snake_body.begin() + 1, snake_body.end(), *(snake_body.begin())) != snake_body.end())//检测有无撞到身体
		return false;
	else if (food.get_location() == *(snake_body.begin()))//检测是否吃到食物
	{
		food.create();
	}
	else if (poi.get_location() == *(snake_body.begin()))//检测是否吃到毒果
	{
		poi.create();
		snake.remove_tail();
		snake.remove_tail();
	}
	else//什么都没撞到
		snake.remove_tail();
	if (snake.get_length() == 1)//检测是否仅剩头部
		return false;
	return true;
}

int main()
{
	snakeChessBoard s;
	s.startGame();
}
