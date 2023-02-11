#ifndef _SCENE_OBJECT_H_
#define _SCENE_OBJECT_H_

#include <vector>
#include <assert.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "model/Mesh.h"

class Mesh;

class Scene_object
{
public:        
                Mesh* p_Mesh { nullptr };     // each node contains relevant render state

                /// bounding box /// 
                glm::vec3  Box_min = glm::vec3(-99999.0f);
                glm::vec3  Box_max = glm::vec3( 99999.0f);

                           Scene_object(unsigned int id) : m_ID(id) {}
                          ~Scene_object();

                     // scene node transform
                     void  set_Position(glm::vec3 position);
                     void  set_Scale(glm::vec3 scale);
                     void  set_Scale(float scale);
                     void  set_Rotation(glm::vec4 rotation);

             unsigned int  get_ID()             const { return m_ID; }
                glm::vec3  get_Local_position() const { return m_Position; }
                glm::vec4  get_Local_rotation() const { return m_Rotation; }
                glm::vec3  get_Local_scale()    const { return m_Scale; }
                glm::vec3  get_World_position();
                glm::vec3  get_World_scale();

std::vector<Scene_object*> get_Children()       const { return m_Children; }
             unsigned int  get_Child_count()    const { return m_Children.size(); }
             Scene_object *get_Parent()         const { return m_Parent; }
             Scene_object *get_Child(unsigned int id);
             Scene_object *get_Child_by_index(unsigned int index);
                     void  add_Child(Scene_object *node);
                     void  remove_Child(unsigned int id); // TODO: think of proper way to unqiuely idetnfiy child nodes 
                                                          // (w/ incrementing node ID or stringed hash ID?)

                // returns the transform of the current node combined with its parent(s)' transform.
                glm::mat4  get_Transform();
                glm::mat4  get_Prev_transform() const { return m_Prev_transform; }

                    // re-calculates this node and its children's transform components if its parent or the 
                    // node itself is dirty.
                    void  update_Transform(bool Update_prev_transform = false);

private:
std::vector<Scene_object*>  m_Children;
             Scene_object*  m_Parent{ nullptr };

                 glm::mat4  m_Transform { glm::mat4(1.0f) };
                 glm::mat4  m_Prev_transform{ glm::mat4(1.0f) };
                 glm::vec3  m_Position { glm::vec3(0.0f) };
                 glm::vec4  m_Rotation { glm::vec4(0.0f) }; // axis-angle for now; test w/ quaternions soon!
                 glm::vec3  m_Scale    { glm::vec3(1.0f) };

                      bool  m_Recalc { false };   // mark the current object's tranform as dirty if it needs to be re-calculated this frame
              unsigned int  m_ID;
};

#endif  //_SCENE_OBJECT_H_