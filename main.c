
typedef struct s_block
{
	char v;
	char dir;
	int id;
	int pv;
} t_block;

typedef struct s_data
{
	t_block *map;
	float pos_X;
	float pos_Y;
} t_data;

int main()
{
	t_data data;
	bool end;


	createMap(&data); //parse ou creer map
	
	while (!end)
	{
		recup_inputs(&data);
		logic();
		draw(&data);
	}
}



