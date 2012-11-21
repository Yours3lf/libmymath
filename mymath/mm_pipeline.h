#ifndef mm_pipeline_h
#define mm_pipeline_h

#include "mm_matrix_stack.h"

namespace mymath
{
  template< typename t >
  class pipeline
  {
    private:
      matrix_stack<t>* modelview;
      matrix_stack<t>* projection;
    protected:

    public:
      void set_model_view_matrix_stack( matrix_stack<t>* mv )
      {
        assert( mv != 0 );
        modelview = mv;
      }

      void set_projection_matrix_stack( matrix_stack<t>* p )
      {
        assert( p != 0 );
        projection = p;
      }

      impl::mat4i<t> get_model_view_projection_matrix()
      {
        return projection->get_matrix() * modelview->get_matrix();
      }

      impl::mat4i<t> get_model_view_matrix()
      {
        return modelview->get_matrix();
      }

      impl::mat4i<t> get_projection_matrix()
      {
        return projection->get_matrix();
      }

      impl::mat3i<t> get_normal_matrix( bool do_normalize = false )
      {
        impl::mat4i<t> tmp = modelview->get_matrix();
        impl::mat3i<t> normal_matrix = impl::mat3i<t>( tmp[0].xyz, tmp[1].xyz, tmp[2].xyz );

        if( do_normalize )
        {
          impl::vec3i<t> r0 = normalize( impl::vec3i<t>( normal_matrix[0].x, normal_matrix[1].x, normal_matrix[2].x ) );
          impl::vec3i<t> r1 = normalize( impl::vec3i<t>( normal_matrix[0].y, normal_matrix[1].y, normal_matrix[2].y ) );
          impl::vec3i<t> r2 = normalize( impl::vec3i<t>( normal_matrix[0].z, normal_matrix[1].z, normal_matrix[2].z ) );

          normal_matrix = impl::mat3i<t>( r0[0], r0[1], r0[2],
                                          r1[0], r1[1], r1[2],
                                          r2[0], r2[1], r2[2] );
        }

        return normal_matrix;
      }

      pipeline() : modelview( 0 ), projection( 0 ) {}
  };

}

#endif
