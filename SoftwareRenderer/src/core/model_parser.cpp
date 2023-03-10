#include "model_parser.h"

Model* ObjParser::Parse(const char* filepath)
{
	std::vector<Model> models;

	std::string name = "";
	std::vector<vec3> vertices;
	std::vector<int> indices;
	int vertCount = 0, idxCount = 0;

	std::ifstream file(filepath, std::ios::in);

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
				models.push_back(Model(name.c_str(), vertCount, &vertices[0], idxCount, &indices[0]));
			}

			iss >> name;
		}
		else if (element == "v")
		{
			float a, b, c;
			iss >> a >> b >> c;
			vertices.push_back(vec3(a, b, c));
			vertCount++;
		}
		else if (element == "f")
		{
			int a, b, c;
			iss >> a >> b >> c;
			indices.push_back(a);
			indices.push_back(b);
			indices.push_back(c);
			idxCount += 3;
		}
	}

	return &models[0];
}
