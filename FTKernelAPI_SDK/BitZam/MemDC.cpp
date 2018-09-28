// MemDC.cpp: implementation of the MemDC class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MemDC.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC( CMemDC, CDC );

// constructor sets up the memory DC
CMemDC::CMemDC( CDC* pDC /* = NULL*/ ) : CDC()
{
    //ASSERT( pDC != NULL );
    if ( pDC != NULL )
    {
        m_pDC = pDC;
        m_pOldBitmap = NULL;
        m_bMemDC = !pDC->IsPrinting();

        if ( m_bMemDC )             // Create a Memory DC
        {
            pDC->GetClipBox( &m_rect );
            CreateCompatibleDC( pDC );
            m_bitmap.CreateCompatibleBitmap( pDC, m_rect.Width(), m_rect.Height() );
            m_pOldBitmap = SelectObject( &m_bitmap );
            SetWindowOrg( m_rect.left, m_rect.top );
        }
        else        // Make a copy of the relevent parts of the current DC for printing
        {
            m_bPrinting = pDC->m_bPrinting;
            m_hDC = pDC->m_hDC;
            m_hAttribDC = pDC->m_hAttribDC;
        }

        m_bValid	= TRUE;
    }
    else
    {
        m_pOldBitmap	= NULL;
        m_pDC	= NULL;
        m_bMemDC	= FALSE;
        m_bValid	= FALSE;
    }
}

void CMemDC::AttachDC( CDC *pDC, CRect *pRect /* = NULL*/ )
{
    ASSERT( m_bValid == FALSE );
    ASSERT( pDC != NULL );
    m_pDC = pDC;
    m_pOldBitmap = NULL;
    m_bMemDC = !pDC->IsPrinting();
    m_bValid	= TRUE;

    if ( m_bMemDC )             // Create a Memory DC
    {
        if ( NULL == pRect )
        {
            pDC->GetClipBox( &m_rect );
        }
        else
        {
            m_rect.CopyRect( pRect );
        }

        CreateCompatibleDC( pDC );
        m_bitmap.CreateCompatibleBitmap( pDC, m_rect.Width(), m_rect.Height() );
        m_pOldBitmap = SelectObject( &m_bitmap );
        SetWindowOrg( m_rect.left, m_rect.top );
    }
    else        // Make a copy of the relevent parts of the current DC for printing
    {
        m_bPrinting = pDC->m_bPrinting;
        m_hDC = pDC->m_hDC;
        m_hAttribDC = pDC->m_hAttribDC;
    }
}

void CMemDC::DettachDC()
{
    if ( !m_bValid )
    {
        return ;
    }

    if ( m_bMemDC )
    {
        // Copy the offscreen bitmap onto the screen.
        if ( m_pDC ->GetSafeHdc() != NULL )
        {
            m_pDC->BitBlt( m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
                           this, m_rect.left, m_rect.top, SRCCOPY );
        }

        //Swap back the original bitmap.
        SelectObject( m_pOldBitmap );
    }
    else
    {
        // All we need to do is replace the DC with an illegal value,
        // this keeps us from accidently deleting the handles associated with
        // the CDC that was passed to the constructor.
        m_hDC = m_hAttribDC = NULL;
    }

    m_pOldBitmap	= NULL;
    m_pDC	= NULL;
    m_bMemDC	= FALSE;
    m_bValid	= FALSE;
}

// Destructor copies the contents of the mem DC to the original DC
CMemDC::~CMemDC()
{
    if ( !m_bValid )
    {
        return ;
    }

    if ( m_bMemDC )
    {
        // Copy the offscreen bitmap onto the screen.
        if ( m_pDC ->GetSafeHdc() != NULL )
        {
            m_pDC->BitBlt( m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
                           this, m_rect.left, m_rect.top, SRCCOPY );
        }

        //Swap back the original bitmap.
        SelectObject( m_pOldBitmap );
    }
    else
    {
        // All we need to do is replace the DC with an illegal value,
        // this keeps us from accidently deleting the handles associated with
        // the CDC that was passed to the constructor.
        m_hDC = m_hAttribDC = NULL;

    }

    m_pOldBitmap	= NULL;
    m_pDC	= NULL;
    m_bMemDC	= FALSE;
    m_bValid	= FALSE;
}
