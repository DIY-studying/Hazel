#include "hzpch.h"
#include "Cube.h"

namespace Hazel
{
	void Cube::GenerateMesh()
	{
		if (!HasComponent<CMesh>())
		{
			HZ_WARN("Mesh not exist, you should add a CMesh component first");
			return;
		}
			
		
		CMesh& mesh = GetComponent<CMesh>();
		std::vector<Vertex>& vertexs = mesh.vertexs;
		std::vector<uint32_t>& indices = mesh.indices;

		std::vector<Eigen::Vector3f> dir = {
			Eigen::Vector3f::UnitX(),
			Eigen::Vector3f::UnitY(),
			Eigen::Vector3f::UnitZ(),
			-Eigen::Vector3f::UnitX(),
			-Eigen::Vector3f::UnitY(),
			-Eigen::Vector3f::UnitZ(),
		};

		for (const auto& d : dir)
		{
			Eigen::Vector3f u = Eigen::Vector3f(d.z(),  d.x(), d.y());
			Eigen::Vector3f v = d.cross(u);
			HZ_CORE_INFO("{},{},{}",u.x(), u.y(), u.z());
			HZ_CORE_INFO("{},{},{}", v.x(), v.y(), v.z());
			for(int i=0;i<(m_resolution-1)*(m_resolution-1);i++)
			{
				int row = i / (m_resolution-1);
				int col = i % (m_resolution-1);

				float stride = m_size / (m_resolution-1);
				Eigen::Vector3f offset = u * m_size / 2.0f + v * m_size / 2.0f-d * m_size / 2.0f;
				float percentunit = 1.0f / (m_resolution - 1);


				Eigen::Vector3f pos1 = u*col*stride + v*row*stride - offset;
				Eigen::Vector3f pos2 = u * (col + 1) * stride + v * row * stride - offset;
				Eigen::Vector3f pos3 = u *col* stride + v * (row + 1) * stride - offset;
				Eigen::Vector3f pos4 = u * (col + 1) * stride + v * (row + 1) * stride - offset;

				Eigen::Vector2f texCoord1 = Eigen::Vector2f(col * percentunit, row * percentunit);
				Eigen::Vector2f texCoord2 = Eigen::Vector2f((col + 1) * percentunit, row * percentunit);
				Eigen::Vector2f texCoord3 = Eigen::Vector2f(col * percentunit, (row + 1) * percentunit);
				Eigen::Vector2f texCoord4 = Eigen::Vector2f((col + 1) * percentunit, (row + 1) * percentunit);

				int baseIndex = vertexs.size();

				vertexs.push_back({ pos1, d,texCoord1 , m_color });
				vertexs.push_back({ pos3, d,texCoord3 , m_color });
				vertexs.push_back({ pos2, d,texCoord2 , m_color });

				indices.push_back(baseIndex);
				indices.push_back(baseIndex + 1);
				indices.push_back(baseIndex + 2);
			

				vertexs.push_back({ pos2, d,texCoord2 , m_color });
				vertexs.push_back({ pos3, d,texCoord3 , m_color });
				vertexs.push_back({ pos4, d,texCoord4 , m_color });

				indices.push_back(baseIndex + 3);
				indices.push_back(baseIndex + 4);
				indices.push_back(baseIndex + 5);
				
			}
		}
		
	}
}