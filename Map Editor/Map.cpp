#include "Map.h"

Map::Map() : m_initialGrid(LEN * 5, LEN * 5), m_currentClicked(-1)
{
	//default constractor
	std::cout << "Please enter number of rows 0-18 \n";
	std::cin >> m_row;
	std::cout << "Please enter number of cols 0-18 \n";
	std::cin >> m_col;
	
	if (m_row <= LIMIT && m_row > 0 && m_col <= LIMIT && m_col > 0)
	{
		m_objects.assign(m_row, std::vector<Objects*>(m_col, nullptr));
	}

	else
	{
		std::cout << "Wrong input, making default board 10x10 \n";
		m_row = m_col = DEFAULT;
		m_objects.assign(m_row, std::vector<Objects*>(m_col, nullptr));
	}
}

Map::Map(std::fstream &file) : m_initialGrid(LEN * 5, LEN * 5), m_currentClicked(-1)
{
	//call a function that reads from file
	read(m_row, m_col);
}

void Map::run()
{
	m_window.create(sf::VideoMode(700, 700), "Map Editor", sf::Style::Close);

	while (m_window.isOpen())
	{
		event();	
	}
}


void Map::event()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		static bool doorPlaced = false;
		static bool robotPlaced = false;
		//close when x is pressed
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				m_window.close();
				break;
			}
		case sf::Event::MouseButtonReleased:
		{
			if (event.mouseButton.button == sf::Mouse::Button::Left)
			{
				//get pos accordint to window
				sf::Vector2i pos = sf::Mouse::getPosition(m_window);

				//witch quare in toolbar we clicked
				clickedToolbarIndex = m_tool.clickedOn(pos);
				//if clicked inside toolbar
				if (clickedToolbarIndex != -1)
				{
					//inside toolbar
					m_currentClicked = clickedToolbarIndex;

					switch (clickedToolbarIndex)
					{
					case 6: //save
						save();
						break;
					case 7: //trash
						m_objects.assign(m_row, std::vector<Objects*>(m_col, nullptr));
						robotPlaced = false;
						doorPlaced = false;
						break;
					default:
						break;
					}
				}

				//if clicked outside toolbar
				if (m_currentClicked == -1)
					break;

				sf::Vector2i posInGrid = inGrid(pos);

				if (posInGrid.x != -1 && posInGrid.y != -1)
				{
					//we are in grid
					switch (m_currentClicked)
					{
					case 0:	//robot
					{
						if (robotPlaced == true)
							break;
						else
							robotPlaced = true;

						const char& c = m_tool.getCharByIndex(m_currentClicked);
						fNew(c, posInGrid);
						break;
					}
					case 1: //guard
					case 2: //wall
					case 3: //rock
					{
						const char current =
							(m_objects[posInGrid.y][posInGrid.x]) ? m_objects[posInGrid.y][posInGrid.x]->getChar() : ',';
						const char& c = m_tool.getCharByIndex(m_currentClicked);

						if (m_objects[posInGrid.y][posInGrid.x] == nullptr)
						
							fNew(c, posInGrid);
						
						else {
							fNew(c, posInGrid);
							if (current == m_tool.getCharByIndex(ROBOT))
								robotPlaced = false;

							if (current == m_tool.getCharByIndex(DOOR))
								doorPlaced = false;
						}
						break;
					}

					case 4:	//door
					{
						if (doorPlaced == true)
							break;
						else
							doorPlaced = true;

						const char& c = m_tool.getCharByIndex(m_currentClicked);
					
						fNew(c, posInGrid);

						if (m_objects[posInGrid.y][posInGrid.x]->getChar() == m_tool.getCharByIndex(ROBOT))
							robotPlaced = false;

						break;
					}

					case 5:	//cleaner
						if (m_objects[posInGrid.y][posInGrid.x] == nullptr)
							break;

						//if image is on robot or door
						if (m_objects[posInGrid.y][posInGrid.x]->getChar() == m_tool.getCharByIndex(ROBOT))
							robotPlaced = false;

						if (m_objects[posInGrid.y][posInGrid.x]->getChar() == m_tool.getCharByIndex(DOOR))
							doorPlaced = false;

						//delete the pointer in this place
						delete m_objects[posInGrid.y][posInGrid.x];
						m_objects[posInGrid.y][posInGrid.x] = (nullptr);
						break;

					default:
						break;
					}
				}
			}
		}
		break;
		}
	}
	m_window.clear();
	drawScreen(m_window);
	print();
	m_tool.build(m_window);
	m_window.display();

}


void Map::print()
{
	static sf::RectangleShape shape1(sf::Vector2f(m_col*LEN, 1));		//length and width of line
	static sf::RectangleShape shape2(sf::Vector2f(1, m_row*LEN));

	shape1.setPosition(m_initialGrid);
	shape2.setPosition(m_initialGrid);

	for (int i = 0; i < m_objects.size(); i++)
	{
		for (int j = 0; j < m_objects[i].size(); j++) {
			if (m_objects[i][j] != nullptr)
				m_objects[i][j]->draw(m_window);
		}
	}


	for (int i = 0; i <= m_col; i++)
	{
		m_window.draw(shape2);
		shape2.move(LEN, 0);
	}
	//draw a matrix
	for (int i = 0; i <= m_row; i++)
	{
		m_window.draw(shape1);
		shape1.move(0, LEN);		//distance between lines
	}


}


sf::Vector2i Map::inGrid(const sf::Vector2i & pos)
{
	if (pos.x >= m_initialGrid.x &&  pos.x <= m_initialGrid.x + (m_col*LEN)
		&& pos.y >= m_initialGrid.y &&  pos.y <= m_initialGrid.y + (m_row*LEN))
	{
		int x = pos.x - (int)m_initialGrid.x;
		int y = pos.y - (int)m_initialGrid.y;

		int newx = x - (x%LEN);
		int newy = y - (y%LEN);

		int cellx = newx / LEN;
		int celly = newy / LEN;
		return (sf::Vector2i(cellx, celly));
		
	}
	else {
		sf::Vector2i defPos = { -1,-1 };
		return (defPos);
	}

}

void Map::save()
{
	std::ofstream file;

	file.open("board.bomb.txt");
	file << m_row;
	file << "\n";
	file << m_col;
	file << "\n";

	for (int i = 0; i < m_objects.size(); i++)
	{
		for (int j = 0; j < m_objects[i].size(); j++) {
			if (m_objects[i][j] != nullptr)
				file << m_objects[i][j]->getChar();
			else
				file << ' ';
		}
		file << '\n';
	}
	file.close();
}


void Map::drawScreen(sf::RenderWindow & m_window)
{
	sf::Sprite s(*GraphicsManager::get_instance().getTexture(SHAPES));
	s.setPosition(0, 0);
	m_window.draw(s);
}

void Map::read(int &m_row, int &m_col)
{
	std::ifstream file;
	
	file.open("board.bomb.txt");
	if (!file.is_open())
	{
		std::cerr << "The file failed to open";
	}

	//system("cls");
	file >> m_row;
	file >> m_col;
	m_objects.assign(m_row, std::vector<Objects*>(m_col, nullptr));

	for (int i = 0; i < m_row; i++)
		{
			for (int j = 0; j <  m_col; j++) {
				char c = file.get();

				while (c == '\n')
					c = file.get();
			
				if (c != ' ')
					m_objects[i][j] = new Objects(GraphicsManager::get_instance().getTexture(c), c, sf::Vector2f(j*LEN + m_initialGrid.x + 3, i*LEN + m_initialGrid.y + 3));
		
			}
			//file << '\n';
		}
	

	file.close();
}

void Map::fNew(const char & c, sf::Vector2i posInGrid)
{
	m_objects[posInGrid.y][posInGrid.x] = 
			new Objects(GraphicsManager::get_instance().getTexture(m_currentClicked), c,
				sf::Vector2f(posInGrid.x*LEN + m_initialGrid.x + 3, posInGrid.y*LEN + m_initialGrid.y + 3));
}

Map::~Map()
{
}
