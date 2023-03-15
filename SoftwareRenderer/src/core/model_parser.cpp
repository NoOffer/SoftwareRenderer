#include "model_parser.h"

void ObjParser::Parse(const char* filepath, std::vector<Model*>& models)
{
	std::ifstream file(filepath, std::ios::in);

	if (file)
	{
		std::string name = "";
		std::vector<vec3> vertices;
		std::vector<int> indices;
		int vertCount = 0, idxCount = 0, modelCount = 0;

		std::string line;

		while (std::getline(file, line))
		{
			std::istringstream iss(line);

			std::string element;

			iss >> element;

			if (element == "o")
			{
				if (vertCount > 0)
				{
					/*
					CAUTION: Possible memory leak
					*/
					models.push_back(new Model(name.c_str(), vertCount, vertices.data(), idxCount, indices.data()));
					vertices.clear();
					vertCount = 0;
					indices.clear();
					idxCount = 0;
				}

				iss >> name;
			}
			else if (element == "v")
			{
				float a, b, c;
				iss >> a >> b >> c;
				vertices.push_back(vec3(a, b, c));
				vertCount++;
				//std::cout << "v " << a << " " << b << " " << c << std::endl;
			}
			else if (element == "f")
			{
				int a, b, c;
				iss >> a >> b >> c;
				indices.push_back(a);
				// Change from CW to CCW
				indices.push_back(c);
				indices.push_back(b);
				idxCount += 3;
				//std::cout << "f " << a << " " << b << " " << c << std::endl;
			}
		}

		if (vertCount > 0)
		{
			/*
			CAUTION: Possible memory leak
			*/
			models.push_back(new Model(name.c_str(), vertCount, vertices.data(), idxCount, indices.data()));
		}
	}
	else
	{
		throw "[Fatal] Failed To Open File";
	}
}
