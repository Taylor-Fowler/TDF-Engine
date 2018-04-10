//#include "glm\gtc\matrix_transform.hpp"
//#include "glm\gtc\type_ptr.hpp"
//
//#include "ReflectionCubeModule.h"
//
//#include "ShaderModule.h"
//#include "..\ShaderParameter\ShaderParamList.h"
//#include "..\Material\Material.h"
//#include "..\..\Engine\GameObject\GameObject.h"
//#include "..\..\Engine\Components\Camera\Camera.h"
//#include "..\..\Engine\Components\Renderer\Renderer.h"
//#include "..\..\Engine\Components\Transform\Transform.h"
//
//void ReflectionCubeModule::PreRender(Camera *const camera)
//{
//	m_mainProgram->Use();
//
//	glm::mat4 perspective = glm::perspective(1.5708f, 1.0f, 0.02f, 1000.0f);
//	m_mainProgram->SendParam("projectionMatrix", glm::value_ptr(perspective));
//}
//
//
//void ReflectionCubeModule::Render(const glm::mat4& viewMatrix)
//{
//	m_mainProgram->Use();
//
//	for (auto& sub : m_subscriberBuffers)
//	{
//		// Render each face
//		for (int i = 0; i < 6; i++)
//		{
//			const glm::vec3 direction[6] =
//			{
//				{ 1.0f, 0.0f, 0.0f },
//				{ -1.0f, 0.0f, 0.0f },
//				{ 0.0f, 1.0f, 0.0f },
//				{ 0.0f, -1.0f, 0.0f },
//				{ 0.0f, 0.0f, 1.0f },
//				{ 0.0f, 0.0f, -1.0f }
//			};
//			auto position = sub.first->AttachedTo().lock()->GetGameObject().GetTransform()->Position();
//			glm::mat4 viewMatrix = glm::lookAt(position, position + (100.0f * direction[i]), glm::vec3(0.0f, 1.0f, 0.0f));
//			m_mainProgram->SendParam("viewMatrix", glm::value_ptr(viewMatrix));
//		}
//	}
//	
//}
//
//
//void ReflectionCubeModule::Subscribe(std::shared_ptr<ShaderParamList> params)
//{
//	m_subscriberBuffers.insert(
//		std::make_pair<std::shared_ptr<Material>, std::unique_ptr<Framebuffer>>
//		(
//			std::static_pointer_cast<Material>(params), 
//			std::make_unique<Framebuffer>()
//		)
//	);
//}