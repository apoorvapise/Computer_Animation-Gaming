#include "Curve.h"

vector<vec3> segmentPoints;

Curve::Curve()
{
}

Curve::~Curve()
{
}

void Curve::init()
{
	this->control_points_pos = {
		{ 0.0, 8.5, -2.0 },
		{ -3.0, 11.0, 2.3 },
		{ -6.0, 8.5, -2.5 },
		{ -4.0, 5.5, 2.8 },
		{ 1.0, 2.0, -4.0 },
		{ 4.0, 2.0, 3.0 },
		{ 7.0, 8.0, -2.0 },
		{ 3.0, 10.0, 3.7 }
	};
}



void Curve::calculate_curve()
{
	int i1, i2, i3, i4, k, i;
	float u, u2, u3;
	curve_points_pos.clear();

	for (i = 0; i < 8; i++)
	{
		i1 = (i - 1 + 8) % 8;
		i2 = i % 8;
		i3 = (i + 1) % 8;
		i4 = (i + 2) % 8;
		glm::vec3 p1(this->control_points_pos[i1]);
		glm::vec3 p2(this->control_points_pos[i2]);
		glm::vec3 p3(this->control_points_pos[i3]);
		glm::vec3 p4(this->control_points_pos[i4]);


		for (k = 1; k < num_points_per_segment + 1; k++)
		{
			u = k * 1.0f / num_points_per_segment;
			u2 = u * u;
			u3 = u2 * u;

			//create matrices for the catlum-rom equation

			glm::vec4 u_mat = glm::vec4(1.0f, u, u2, u3);
			glm::mat4x4 coeff_mat = glm::mat4x4(0.0f, 1.0f, 0.0f, 0.0f, -0.5f, 0.0f, 0.5f, 0.0f, 1.0f, -2.5f, 2.0f, -0.5f, -0.5f, 1.5f, -1.5f, 0.5f);
			glm::mat4x3 points = glm::mat4x3(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p3.y, p3.z, p4.x, p4.y, p4.z);

			//in glm we reverse multiply in the order we actually want to multiply them
			glm::vec3 result = points * coeff_mat * u_mat;

			//insert all 200 *8 points in a vector
			curve_points_pos.push_back(result);

		}
	
		


	}


}

