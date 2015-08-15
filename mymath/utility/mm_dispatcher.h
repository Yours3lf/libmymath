#pragma once

//based on the fast, constant time multi-dispatcher design pattern
template<class lhs,
class rhs = lhs,
class ret = void,
class cbk = ret( *)( lhs, rhs )>
class dispatcher
{
  typedef std::vector<cbk> matrix;
  matrix callbacks;
  int elements;
public:
  dispatcher() : elements( 0 )
  {
  }

  void set_elements( int num )
  {
    elements = num;
    callbacks.resize( num * num );

    for( int c = 0; c < num * num; ++c )
      callbacks[c] = 0;
  }

  template<class _lhs, class _rhs>
  void add( cbk func )
  {
    int idx_lhs = _lhs::get_class_idx();
    int idx_rhs = _rhs::get_class_idx();

    callbacks[idx_lhs * elements + idx_rhs] = func;
  }

  ret go( lhs _lhs, rhs _rhs )
  {
    int idx_lhs = _lhs->get_class_index();
    int idx_rhs = _rhs->get_class_index();

    assert( idx_lhs >= 0 || idx_rhs >= 0 || idx_lhs < elements || idx_rhs < elements );
    assert( callbacks[idx_lhs * elements + idx_rhs] != 0 );

    return callbacks[idx_lhs * elements + idx_rhs]( _lhs, _rhs );
  }
};