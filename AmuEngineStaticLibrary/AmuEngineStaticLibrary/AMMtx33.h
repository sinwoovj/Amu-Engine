/******************************************************************************/
/*!
\par        Project: Amu Engine
\file       AMMtx33.h

\author     Shinwoo Choi
\date       Oct 30, 2024

\brief      Header file for the library settings.
*/
/******************************************************************************/

#ifndef MTX33_H
#define MTX33_H

// ---------------------------------------------------------------------------
// Defines

#define Mtx33RowCol(pMtx, row, col) (pMtx)->m[(row)][(col)]

// ---------------------------------------------------------------------------
// Struct/Class definitions

/*!
  Matrix is stored in column major format,
  ie. the translation term is in the right most column.

  m[0][0] m[0][1] m[0][2] \n
  m[1][0] m[1][1] m[1][2] \n
  m[2][0] m[2][1] m[2][2]
  */

#include <AMExport.h>
#include <AMMath.h>

typedef struct Mtx33
{
    float	m[3][3];
}Mtx33;

// ---------------------------------------------------------------------------

#ifdef __cplusplus 
extern "C"
{
#endif

    // ---------------------------------------------------------------------------

    /******************************************************************************/
    /*!
      \fn         void Mtx33Identity (Mtx33* pResult)

      \brief      Set pResult to identity matrix.

      \param      [out] pResult
      Pointer to Mtx33 to be set.

*/
/******************************************************************************/
    API void 		Mtx33Identity(Mtx33* pResult);

    /******************************************************************************/
    /*!
      \fn         void Mtx33Transpose(Mtx33* pResult,
      Mtx33* pMtx)

      \brief      Set pResult to the transpose of pMtx.

      \param      [out] pResult
      Pointer to Mtx33 to be set.

      \param      [in] pMtx
      Pointer to Mtx33 for input.

*/
/******************************************************************************/
    API void 		Mtx33Transpose(Mtx33* pResult, Mtx33* pMtx);

    /******************************************************************************/
    /*!
      \fn         float Mtx33Inverse(Mtx33* pResult,
      Mtx33* pMtx)

      \brief      Set pResult to the inverse of pMtx.

      \param      [out] pResult
      Pointer to Mtx33 to be set.

      \param      [in] pMtx
      Pointer to Mtx33 for input.

      \retval     float
      Returns the determinant of pMtx.
      */
      /******************************************************************************/
    API float			Mtx33Inverse(Mtx33* pResult, Mtx33* pMtx);

    /******************************************************************************/
    /*!
      \fn         void Mtx33InvTranspose(Mtx33* pResult,
      Mtx33* pMtx)

      \brief      Set pResult to the transpose of the inverse of pMtx.

      \param      [out] pResult
      Pointer to Mtx33 to be set.

      \param      [in] pMtx
      Pointer to Mtx33 for input.

*/
/******************************************************************************/
    API void 		Mtx33InvTranspose(Mtx33* pResult, Mtx33* pMtx);

    /******************************************************************************/
    /*!
      \fn         void Mtx33Concat(Mtx33* pResult,
      Mtx33* pMtx0,
      Mtx33* pMtx1)

      \brief      Set pResult to the multiplication of pMtx0 with pMtx1.

      \param      [out] pResult
      Pointer to Mtx33 to be set.

      \param      [in] pMtx0
      Pointer to Mtx33 for input.

      \param      [in] pMtx1
      Pointer to Mtx33 for input.

*/
/******************************************************************************/
    API void 		Mtx33Concat(Mtx33* pResult, Mtx33* pMtx0, Mtx33* pMtx1);

    /******************************************************************************/
    /*!
      \fn         void Mtx33Orthogonalize(Mtx33* pResult,
      Mtx33* pMtx)

      \brief      Set pResult to the orthogonalization of pMtx.

      \warning    Function not implemented.

      \param      [out] pResult
      Pointer to Mtx33 to be set.

      \param      [in] pMtx
      Pointer to Mtx33 for input.

*/
/******************************************************************************/
    API void 		Mtx33Orthogonalize(Mtx33* pResult, Mtx33* pMtx);

    /******************************************************************************/
    /*!
      \fn         float Mtx33Determinant(Mtx33* pMtx)

      \brief      Calculate the determinant of pMtx.

      \param      [in] pMtx
      Pointer to Mtx33 for input.

      \retval     float
      Returns the determinant of pMtx.
      */
      /******************************************************************************/
    API float			Mtx33Determinant(Mtx33* pMtx);

    // ---------------------------------------------------------------------------

    /******************************************************************************/
    /*!
      \fn         void Mtx33SetCol(Mtx33* pResult,
      unsigned int col,
      Vec2* pVec)

      \brief      Set the first and second element of the selected column of pResult
      to the x and y values of pVec respectively. The last element of the
      column will be set automatically.

      \param      [in,out] pResult
      Pointer to Mtx33 to be set.

      \param      [in] col
      The selected column of pResult.

      \param      [in] pVec
      Pointer to Vec2 for input.

*/
/******************************************************************************/
    API void 		Mtx33SetCol(Mtx33* pResult, unsigned int col, Vec2* pVec);

    /******************************************************************************/
    /*!
      \fn         void Mtx33SetRow(Mtx33* pResult,
      unsigned int row,
      Vec2* pVec)

      \brief      Set the first and second element of the selected row of pResult
      to the x and y values of pVec respectively. The last element of the
      row will be set automatically.

      \param      [in,out] pResult
      Pointer to Mtx33 to be set.

      \param      [in] row
      The selected row of pResult.

      \param      [in] pVec
      Pointer to Vec2 for input.

*/
/******************************************************************************/
    API void 		Mtx33SetRow(Mtx33* pResult, unsigned int row, Vec2* pVec);

    /******************************************************************************/
    /*!
      \fn         void Mtx33GetCol(Vec2* pResult,
      Mtx33* pMtx,
      unsigned int col)

      \brief      Set the x and y values of pResult with the first and second element of
      the selected column of pMtx respectively.

      \param      [out] pResult
      Pointer to Vec2 to be set.

      \param      [in] pMtx
      Pointer to Mtx33 for input.

      \param      [in] col
      The selected column of pResult.

*/
/******************************************************************************/
    API void 		Mtx33GetCol(Vec2* pResult, Mtx33* pMtx, unsigned int col);

    /******************************************************************************/
    /*!
      \fn         void Mtx33GetRow(Vec2* pResult,
      Mtx33* pMtx
      unsigned int row)

      \brief      Set the x and y values of pResult with the first and second element of
      the selected row of pMtx respectively.

      \param      [out] pResult
      Pointer to Vec2 to be set.

      \param      [in] pMtx
      Pointer to Mtx33 for input.

      \param      [in] row
      The selected row of pResult.

*/
/******************************************************************************/
    API void			Mtx33GetRow(Vec2* pResult, Mtx33* pMtx, unsigned int row);

    // ---------------------------------------------------------------------------

    /******************************************************************************/
    /*!
      \fn         void Mtx33Trans(Mtx33* pResult,
      float x,
      float y)

      \brief      Set pResult to the translation matrix of x and y.

      \param      [out] pResult
      Pointer to Mtx33 to be set.

      \param      [in] x
      Translation along the x-axis.

      \param      [in] y
      Translation along the y-axis.

*/
/******************************************************************************/
    API void 		Mtx33Trans(Mtx33* pResult, float x, float y);

    /******************************************************************************/
    /*!
      \fn         void Mtx33TransApply(Mtx33* pResult,
      Mtx33* pMtx,
      float x,
      float y)

      \brief      Set pResult to the multiplication of translation matrix of x and y
      with pMtx.

      \param      [out] pResult
      Pointer to Mtx33 to be set.

      \param      [in] pMtx
      Pointer to Mtx33 for input.

      \param      [in] x
      Translation along the x-axis.

      \param      [in] y
      Translation along the y-axis.

*/
/******************************************************************************/
    API void 		Mtx33TransApply(Mtx33* pResult, Mtx33* pMtx, float x, float y);

    /******************************************************************************/
    /*!
      \fn         void Mtx33Scale(Mtx33* pResult,
      float x,
      float y)

      \brief      Set pResult to the scaling matrix of x and y.

      \param      [out] pResult
      Pointer to Mtx33 to be set.

      \param      [in] x
      Scaling along the x-axis.

      \param      [in] y
      Scaling along the y-axis.

*/
/******************************************************************************/
    API void 		Mtx33Scale(Mtx33* pResult, float x, float y);

    /******************************************************************************/
    /*!
      \fn         void Mtx33ScaleApply(Mtx33* pResult,
      Mtx33* pMtx,
      float x,
      float y)

      \brief      Set pResult to the multiplication of scaling matrix of x and y
      with pMtx.

      \param      [out] pResult
      Pointer to Mtx33 to be set.

      \param      [in] pMtx
      Pointer to Mtx33 for input.

      \param      [in] x
      Scaling along the x-axis.

      \param      [in] y
      Scaling along the y-axis.

*/
/******************************************************************************/
    API void 		Mtx33ScaleApply(Mtx33* pResult, Mtx33* pMtx, float x, float y);

    /******************************************************************************/
    /*!
      \fn         void Mtx33Rot(Mtx33* pResult,
      float angle)

      \brief      Set pResult to the rotation matrix of angle in radians
      rotating counter-clockwise.

      \param      [out] pResult
      Pointer to Mtx33 to be set.

      \param      [in] angle
      Angle in radians rotating counter-clockwise.

*/
/******************************************************************************/
    API void 		Mtx33Rot(Mtx33* pResult, float angle);

    /******************************************************************************/
    /*!
      \fn         void Mtx33RotDeg(Mtx33* pResult,
      float angle)

      \brief      Set pResult to the rotation matrix of angle in degrees
      rotating counter-clockwise.

      \param      [out] pResult
      Pointer to Mtx33 to be set.

      \param      [in] angle
      Angle in degress rotating counter-clockwise.

*/
/******************************************************************************/
    API void 		Mtx33RotDeg(Mtx33* pResult, float angle);

    // ---------------------------------------------------------------------------

    /******************************************************************************/
    /*!
      \fn         void Mtx33MultVec(Vec2* pResult,
      Mtx33* pMtx,
      Vec2* pVec)

      \brief      Set pResult to the multiplication of pMtx with pVec.

      \param      [out] pResult
      Pointer to Mtx33 to be set.

      \param      [in] pMtx
      Pointer to Mtx33 for input.

      \param      [in] pVec
      Pointer to Vec2 for input.

*/
/******************************************************************************/
    API void 		Mtx33MultVec(Vec2* pResult, Mtx33* pMtx, Vec2* pVec);

    /******************************************************************************/
    /*!
      \fn         void Mtx33MultVecArray(Vec2* pResult,
      Mtx33* pMtx,
      Vec2* pVec,
      unsigned int count)

      \brief      Set an array of vectors (pResult) to the multiplication
      of pMtx with an array of vectors (pVec) of size (count).

      \warning    Size of pResult should be not less than count.

      \param      [out] pResult
      Pointer to an array of Mtx33 to be set.

      \param      [in] pMtx
      Pointer to Mtx33 for input.

      \param      [in] pVec
      Pointer to an array of Vec2 for input.

      \param      [in] count
      Number of elements in pVec to be multiplied.

*/
/******************************************************************************/
    API void 		Mtx33MultVecArray(Vec2* pResult, Mtx33* pMtx, Vec2* pVec, unsigned int count);


    API void 		Mtx33MultVecSR(Vec2* pResult, Mtx33* pMtx, Vec2* pVec);
    API void 		Mtx33MultVecArraySR(Vec2* pResult, Mtx33* pMtx, Vec2* pVec, unsigned int count);

    // ---------------------------------------------------------------------------




#ifdef __cplusplus 
}
#endif

#endif // MTX_H
