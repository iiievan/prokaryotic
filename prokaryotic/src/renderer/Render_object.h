#pragma once

#include <stdint.h>
#include <iostream>
#include <stdio.h>
#include <assert.h>

namespace PROKARYOTIC
{
     enum e_RENDER_OBJECT_TYPES :std::uint16_t
    {
        CLASS_NA = 0,
        CLASS_SCENE_OBJECT,
        CLASS_LIGHT_SOURCE,
    };

    struct unique_id
    {
        union
        {
            struct
            {
                std::uint16_t    MIN;
                std::uint16_t    MAJ;
                std::uint16_t    GROUP;
                std::uint16_t    CLASS;
            };
            uint64_t  raw;
        };

        unique_id(std::uint16_t min, std::uint16_t maj, std::uint16_t gr, std::uint16_t cl)
            :MIN(min), MAJ(maj), GROUP(gr), CLASS(cl) {}
        unique_id(std::uint64_t raw)
            :raw(raw) {}
    };

	class Render_object
	{
	public:

		Render_object(e_RENDER_OBJECT_TYPES obj_type)
         : m_ID(0)
        {
            m_ID.raw   = m_generate_ID();
            m_ID.GROUP = static_cast<std::uint16_t>(obj_type);
        }
                    virtual unique_id  get_render_object_ID()   const { return m_ID;  }
        virtual e_RENDER_OBJECT_TYPES  get_render_object_TYPE() const { return static_cast<e_RENDER_OBJECT_TYPES>(m_ID.CLASS); }

	protected:
                unique_id  m_ID;   // ID of the object
    private:             
            std::uint64_t  m_generate_ID();
	};
    
    static unique_id m_Unique_ID;
}