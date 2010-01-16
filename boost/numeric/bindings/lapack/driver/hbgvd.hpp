//
// Copyright (c) 2002--2010
// Toon Knapen, Karl Meerbergen, Kresimir Fresl,
// Thomas Klimpel and Rutger ter Borg
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// THIS FILE IS AUTOMATICALLY GENERATED
// PLEASE DO NOT EDIT!
//

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_HBGVD_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_HBGVD_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/bandwidth.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/traits/detail/utils.hpp>
#include <boost/numeric/bindings/uplo_tag.hpp>
#include <boost/numeric/bindings/value.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

//
// The LAPACK-backend for hbgvd is the netlib-compatible backend.
//
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/detail/lapack_option.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//
// The detail namespace contains value-type-overloaded functions that
// dispatch to the appropriate back-end LAPACK-routine.
//
namespace detail {

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
template< typename UpLo >
inline std::ptrdiff_t hbgvd( const char jobz, UpLo, const fortran_int_t n,
        const fortran_int_t ka, const fortran_int_t kb,
        std::complex<float>* ab, const fortran_int_t ldab,
        std::complex<float>* bb, const fortran_int_t ldbb, float* w,
        std::complex<float>* z, const fortran_int_t ldz,
        std::complex<float>* work, const fortran_int_t lwork, float* rwork,
        const fortran_int_t lrwork, fortran_int_t* iwork,
        const fortran_int_t liwork ) {
    fortran_int_t info(0);
    LAPACK_CHBGVD( &jobz, &lapack_option< UpLo >::value, &n, &ka, &kb, ab,
            &ldab, bb, &ldbb, w, z, &ldz, work, &lwork, rwork, &lrwork, iwork,
            &liwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
template< typename UpLo >
inline std::ptrdiff_t hbgvd( const char jobz, UpLo, const fortran_int_t n,
        const fortran_int_t ka, const fortran_int_t kb,
        std::complex<double>* ab, const fortran_int_t ldab,
        std::complex<double>* bb, const fortran_int_t ldbb, double* w,
        std::complex<double>* z, const fortran_int_t ldz,
        std::complex<double>* work, const fortran_int_t lwork, double* rwork,
        const fortran_int_t lrwork, fortran_int_t* iwork,
        const fortran_int_t liwork ) {
    fortran_int_t info(0);
    LAPACK_ZHBGVD( &jobz, &lapack_option< UpLo >::value, &n, &ka, &kb, ab,
            &ldab, bb, &ldbb, w, z, &ldz, work, &lwork, rwork, &lrwork, iwork,
            &liwork, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to hbgvd.
//
template< typename Value >
struct hbgvd_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;
    typedef tag::column_major order;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixAB, typename MatrixBB, typename VectorW,
            typename MatrixZ, typename WORK, typename RWORK, typename IWORK >
    static std::ptrdiff_t invoke( const char jobz, MatrixAB& ab, MatrixBB& bb,
            VectorW& w, MatrixZ& z, detail::workspace3< WORK, RWORK,
            IWORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::uplo_tag< MatrixAB >::type uplo;
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixAB >::type >::type,
                typename remove_const< typename value<
                MatrixBB >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename value< MatrixAB >::type >::type,
                typename remove_const< typename value<
                MatrixZ >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixAB >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixBB >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorW >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixZ >::value) );
        BOOST_ASSERT( bindings::bandwidth(ab, uplo()) >= 0 );
        BOOST_ASSERT( bindings::bandwidth(bb, uplo()) >= 0 );
        BOOST_ASSERT( bindings::size(work.select(fortran_int_t())) >=
                min_size_iwork( jobz, bindings::size_column(ab) ));
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_rwork( jobz, bindings::size_column(ab) ));
        BOOST_ASSERT( bindings::size(work.select(value_type())) >=
                min_size_work( jobz, bindings::size_column(ab) ));
        BOOST_ASSERT( bindings::size_column(ab) >= 0 );
        BOOST_ASSERT( bindings::size_minor(ab) == 1 ||
                bindings::stride_minor(ab) == 1 );
        BOOST_ASSERT( bindings::size_minor(bb) == 1 ||
                bindings::stride_minor(bb) == 1 );
        BOOST_ASSERT( bindings::size_minor(z) == 1 ||
                bindings::stride_minor(z) == 1 );
        BOOST_ASSERT( bindings::stride_major(ab) >= bindings::bandwidth(ab,
                uplo())+1 );
        BOOST_ASSERT( bindings::stride_major(bb) >= bindings::bandwidth(bb,
                uplo())+1 );
        BOOST_ASSERT( jobz == 'N' || jobz == 'V' );
        return detail::hbgvd( jobz, uplo(), bindings::size_column(ab),
                bindings::bandwidth(ab, uplo()), bindings::bandwidth(bb,
                uplo()), bindings::begin_value(ab),
                bindings::stride_major(ab), bindings::begin_value(bb),
                bindings::stride_major(bb), bindings::begin_value(w),
                bindings::begin_value(z), bindings::stride_major(z),
                bindings::begin_value(work.select(value_type())),
                bindings::size(work.select(value_type())),
                bindings::begin_value(work.select(real_type())),
                bindings::size(work.select(real_type())),
                bindings::begin_value(work.select(fortran_int_t())),
                bindings::size(work.select(fortran_int_t())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixAB, typename MatrixBB, typename VectorW,
            typename MatrixZ >
    static std::ptrdiff_t invoke( const char jobz, MatrixAB& ab, MatrixBB& bb,
            VectorW& w, MatrixZ& z, minimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::uplo_tag< MatrixAB >::type uplo;
        bindings::detail::array< value_type > tmp_work( min_size_work( jobz,
                bindings::size_column(ab) ) );
        bindings::detail::array< real_type > tmp_rwork( min_size_rwork( jobz,
                bindings::size_column(ab) ) );
        bindings::detail::array< fortran_int_t > tmp_iwork(
                min_size_iwork( jobz, bindings::size_column(ab) ) );
        return invoke( jobz, ab, bb, w, z, workspace( tmp_work, tmp_rwork,
                tmp_iwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixAB, typename MatrixBB, typename VectorW,
            typename MatrixZ >
    static std::ptrdiff_t invoke( const char jobz, MatrixAB& ab, MatrixBB& bb,
            VectorW& w, MatrixZ& z, optimal_workspace work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::uplo_tag< MatrixAB >::type uplo;
        value_type opt_size_work;
        real_type opt_size_rwork;
        fortran_int_t opt_size_iwork;
        detail::hbgvd( jobz, uplo(), bindings::size_column(ab),
                bindings::bandwidth(ab, uplo()), bindings::bandwidth(bb,
                uplo()), bindings::begin_value(ab),
                bindings::stride_major(ab), bindings::begin_value(bb),
                bindings::stride_major(bb), bindings::begin_value(w),
                bindings::begin_value(z), bindings::stride_major(z),
                &opt_size_work, -1, &opt_size_rwork, -1, &opt_size_iwork, -1 );
        bindings::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        bindings::detail::array< real_type > tmp_rwork(
                traits::detail::to_int( opt_size_rwork ) );
        bindings::detail::array< fortran_int_t > tmp_iwork(
                opt_size_iwork );
        return invoke( jobz, ab, bb, w, z, workspace( tmp_work, tmp_rwork,
                tmp_iwork ) );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const char jobz,
            const std::ptrdiff_t n ) {
        if ( n < 2 )
            return 1;
        else {
            if ( jobz == 'N' )
                return n;
            else
                return 2*n*n;
        }
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array rwork.
    //
    static std::ptrdiff_t min_size_rwork( const char jobz,
            const std::ptrdiff_t n ) {
        if ( n < 2 )
            return 1;
        else {
            if ( jobz == 'N' )
                return n;
            else
                return 1 + 5*n + 2*n*n;
        }
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array iwork.
    //
    static std::ptrdiff_t min_size_iwork( const char jobz,
            const std::ptrdiff_t n ) {
        if ( jobz == 'N' || n < 2 )
            return 1;
        else
            return 3 + 5*n;
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the hbgvd_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for hbgvd. Its overload differs for
// * MatrixAB&
// * MatrixBB&
// * VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, MatrixAB& ab, MatrixBB& bb, VectorW& w,
        MatrixZ& z, Workspace work ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, work );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * MatrixAB&
// * MatrixBB&
// * VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ >
inline typename boost::disable_if< detail::is_workspace< MatrixZ >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, MatrixAB& ab, MatrixBB& bb, VectorW& w,
        MatrixZ& z ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, optimal_workspace() );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * const MatrixAB&
// * MatrixBB&
// * VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, const MatrixAB& ab, MatrixBB& bb, VectorW& w,
        MatrixZ& z, Workspace work ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, work );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * const MatrixAB&
// * MatrixBB&
// * VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ >
inline typename boost::disable_if< detail::is_workspace< MatrixZ >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, const MatrixAB& ab, MatrixBB& bb, VectorW& w,
        MatrixZ& z ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, optimal_workspace() );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * MatrixAB&
// * const MatrixBB&
// * VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, MatrixAB& ab, const MatrixBB& bb, VectorW& w,
        MatrixZ& z, Workspace work ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, work );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * MatrixAB&
// * const MatrixBB&
// * VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ >
inline typename boost::disable_if< detail::is_workspace< MatrixZ >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, MatrixAB& ab, const MatrixBB& bb, VectorW& w,
        MatrixZ& z ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, optimal_workspace() );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * const MatrixAB&
// * const MatrixBB&
// * VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, const MatrixAB& ab, const MatrixBB& bb,
        VectorW& w, MatrixZ& z, Workspace work ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, work );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * const MatrixAB&
// * const MatrixBB&
// * VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ >
inline typename boost::disable_if< detail::is_workspace< MatrixZ >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, const MatrixAB& ab, const MatrixBB& bb,
        VectorW& w, MatrixZ& z ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, optimal_workspace() );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * MatrixAB&
// * MatrixBB&
// * const VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, MatrixAB& ab, MatrixBB& bb, const VectorW& w,
        MatrixZ& z, Workspace work ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, work );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * MatrixAB&
// * MatrixBB&
// * const VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ >
inline typename boost::disable_if< detail::is_workspace< MatrixZ >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, MatrixAB& ab, MatrixBB& bb, const VectorW& w,
        MatrixZ& z ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, optimal_workspace() );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * const MatrixAB&
// * MatrixBB&
// * const VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, const MatrixAB& ab, MatrixBB& bb,
        const VectorW& w, MatrixZ& z, Workspace work ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, work );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * const MatrixAB&
// * MatrixBB&
// * const VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ >
inline typename boost::disable_if< detail::is_workspace< MatrixZ >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, const MatrixAB& ab, MatrixBB& bb,
        const VectorW& w, MatrixZ& z ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, optimal_workspace() );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * MatrixAB&
// * const MatrixBB&
// * const VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, MatrixAB& ab, const MatrixBB& bb,
        const VectorW& w, MatrixZ& z, Workspace work ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, work );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * MatrixAB&
// * const MatrixBB&
// * const VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ >
inline typename boost::disable_if< detail::is_workspace< MatrixZ >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, MatrixAB& ab, const MatrixBB& bb,
        const VectorW& w, MatrixZ& z ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, optimal_workspace() );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * const MatrixAB&
// * const MatrixBB&
// * const VectorW&
// * MatrixZ&
// * User-defined workspace
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, const MatrixAB& ab, const MatrixBB& bb,
        const VectorW& w, MatrixZ& z, Workspace work ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, work );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * const MatrixAB&
// * const MatrixBB&
// * const VectorW&
// * MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ >
inline typename boost::disable_if< detail::is_workspace< MatrixZ >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, const MatrixAB& ab, const MatrixBB& bb,
        const VectorW& w, MatrixZ& z ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, optimal_workspace() );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * MatrixAB&
// * MatrixBB&
// * VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, MatrixAB& ab, MatrixBB& bb, VectorW& w,
        const MatrixZ& z, Workspace work ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, work );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * MatrixAB&
// * MatrixBB&
// * VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ >
inline typename boost::disable_if< detail::is_workspace< MatrixZ >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, MatrixAB& ab, MatrixBB& bb, VectorW& w,
        const MatrixZ& z ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, optimal_workspace() );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * const MatrixAB&
// * MatrixBB&
// * VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, const MatrixAB& ab, MatrixBB& bb, VectorW& w,
        const MatrixZ& z, Workspace work ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, work );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * const MatrixAB&
// * MatrixBB&
// * VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ >
inline typename boost::disable_if< detail::is_workspace< MatrixZ >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, const MatrixAB& ab, MatrixBB& bb, VectorW& w,
        const MatrixZ& z ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, optimal_workspace() );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * MatrixAB&
// * const MatrixBB&
// * VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, MatrixAB& ab, const MatrixBB& bb, VectorW& w,
        const MatrixZ& z, Workspace work ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, work );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * MatrixAB&
// * const MatrixBB&
// * VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ >
inline typename boost::disable_if< detail::is_workspace< MatrixZ >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, MatrixAB& ab, const MatrixBB& bb, VectorW& w,
        const MatrixZ& z ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, optimal_workspace() );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * const MatrixAB&
// * const MatrixBB&
// * VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, const MatrixAB& ab, const MatrixBB& bb,
        VectorW& w, const MatrixZ& z, Workspace work ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, work );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * const MatrixAB&
// * const MatrixBB&
// * VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ >
inline typename boost::disable_if< detail::is_workspace< MatrixZ >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, const MatrixAB& ab, const MatrixBB& bb,
        VectorW& w, const MatrixZ& z ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, optimal_workspace() );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * MatrixAB&
// * MatrixBB&
// * const VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, MatrixAB& ab, MatrixBB& bb, const VectorW& w,
        const MatrixZ& z, Workspace work ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, work );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * MatrixAB&
// * MatrixBB&
// * const VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ >
inline typename boost::disable_if< detail::is_workspace< MatrixZ >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, MatrixAB& ab, MatrixBB& bb, const VectorW& w,
        const MatrixZ& z ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, optimal_workspace() );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * const MatrixAB&
// * MatrixBB&
// * const VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, const MatrixAB& ab, MatrixBB& bb,
        const VectorW& w, const MatrixZ& z, Workspace work ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, work );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * const MatrixAB&
// * MatrixBB&
// * const VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ >
inline typename boost::disable_if< detail::is_workspace< MatrixZ >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, const MatrixAB& ab, MatrixBB& bb,
        const VectorW& w, const MatrixZ& z ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, optimal_workspace() );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * MatrixAB&
// * const MatrixBB&
// * const VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, MatrixAB& ab, const MatrixBB& bb,
        const VectorW& w, const MatrixZ& z, Workspace work ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, work );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * MatrixAB&
// * const MatrixBB&
// * const VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ >
inline typename boost::disable_if< detail::is_workspace< MatrixZ >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, MatrixAB& ab, const MatrixBB& bb,
        const VectorW& w, const MatrixZ& z ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, optimal_workspace() );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * const MatrixAB&
// * const MatrixBB&
// * const VectorW&
// * const MatrixZ&
// * User-defined workspace
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, const MatrixAB& ab, const MatrixBB& bb,
        const VectorW& w, const MatrixZ& z, Workspace work ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, work );
}

//
// Overloaded function for hbgvd. Its overload differs for
// * const MatrixAB&
// * const MatrixBB&
// * const VectorW&
// * const MatrixZ&
// * Default workspace-type (optimal)
//
template< typename MatrixAB, typename MatrixBB, typename VectorW,
        typename MatrixZ >
inline typename boost::disable_if< detail::is_workspace< MatrixZ >,
        std::ptrdiff_t >::type
hbgvd( const char jobz, const MatrixAB& ab, const MatrixBB& bb,
        const VectorW& w, const MatrixZ& z ) {
    return hbgvd_impl< typename value< MatrixAB >::type >::invoke( jobz,
            ab, bb, w, z, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
