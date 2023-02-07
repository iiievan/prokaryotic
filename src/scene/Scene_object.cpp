#include "Scene_object.h"
#include <glm/gtx/string_cast.hpp>

Scene_object::~Scene_object()
{
    for (unsigned int i = 0; i < m_Children.size(); ++i)
    {
        delete m_Children[i];
    }  
}

void  Scene_object::set_Position(glm::vec3 position)
{
    m_Position = position;
    m_Recalc = true;
}

void  Scene_object::set_Scale(glm::vec3 scale)
{
    m_Scale = scale;
    m_Recalc = true;
}

void  Scene_object::set_Scale(float scale)
{
    m_Scale = glm::vec3(scale);
    m_Recalc = true;
}
 
void  Scene_object::set_Rotation(glm::vec4 rotation)
{
    m_Rotation = rotation;
    m_Recalc = true;
}

glm::vec3  Scene_object::get_World_position()
{
    glm::mat4 transform = get_Transform();
    glm::vec4 pos = transform * glm::vec4(m_Position, 1.0f);

    glm::vec3 result = glm::vec3(pos.x, pos.y, pos.z);

    return result;
}

glm::vec3  Scene_object::get_World_scale()
{
    glm::mat4 transform = get_Transform();
    glm::vec3 scale = glm::vec3(transform[0][0], transform[1][1], transform[2][2]);

    if (scale.x < 0.0f) scale.x *= -1.0f;
    if (scale.y < 0.0f) scale.y *= -1.0f;
    if(scale.z < 0.0f) scale.z *= -1.0f;

    return scale;
}

void  Scene_object::add_Child(Scene_object *obj)
{ 
    // Scene objects aren't allowed to exist under multiple parents.
    if (obj->m_Parent)
        obj->m_Parent->remove_Child(obj->m_ID);

    obj->m_Parent = this;
    m_Children.push_back(obj);
}

void  Scene_object::remove_Child(unsigned int id) 
{
    auto it = std::find(m_Children.begin(), m_Children.end(), get_Child(id));

    if(it != m_Children.end())
        m_Children.erase(it);
}

Scene_object* Scene_object::get_Child(unsigned int id)
{
    for (unsigned int i = 0; i < m_Children.size(); ++i)
    {
        if(m_Children[i]->get_ID() == id)
            return m_Children[i];
    }

    return nullptr;
}

Scene_object* Scene_object::get_Child_by_index(unsigned int index)
{
    assert(index < get_Child_count());

    return m_Children[index];
}

glm::mat4  Scene_object::get_Transform()
{
    if (m_Recalc)
        update_Transform(false);

    return m_Transform;
}

void  Scene_object::update_Transform(bool Update_prev_transform)
{
    // if specified, store current transform as prev transform (for calculating motion vectors)
    if (Update_prev_transform)
        m_Prev_transform = m_Transform;

    // we only do this if the node itself or its parent is flagged as dirty
    if (m_Recalc)
    {
        // first translation , then scale, then rotate.
        glm::vec4 vec(m_Position.x, m_Position.y, m_Position.z, 1.0f);;
        m_Transform = glm::mat4(1.0f);
        m_Transform = glm::translate(m_Transform, glm::vec3(1.0f, 1.0f, 0.0f));
        vec = m_Transform * vec;
        m_Position = glm::vec3(vec);

        printf("m_Position:%s\n", glm::to_string(m_Position).c_str());

        //m_Transform = glm::translate(m_Position);
        //m_Transform = glm::scale(m_Transform, m_Scale); // TODO: order is off here for some reason, figure out why
        //m_Transform = glm::rotate(m_Transform, m_Rotation.xyz, m_Rotation.w);

        if (m_Parent)
        {
            m_Transform = m_Parent->m_Transform * m_Transform;
        }        
    }

    for (int i = 0; i < m_Children.size(); ++i)
    {
        if (m_Recalc)
        {
            m_Children[i]->m_Recalc = true;
        }

        m_Children[i]->update_Transform(Update_prev_transform);
    }

    m_Recalc = false;
}

