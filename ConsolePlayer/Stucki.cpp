﻿/*
 * copyright (c) 2015 Mewiteor
 *
 * This file is part of ConsolePlayer.
 *
 * ConsolePlayer is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * ConsolePlayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with ConsolePlayer; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */
#include "Stucki.h"


CStucki::CStucki(unsigned int width, unsigned int height)
    :CErrorDiffusion(width, height)
{
}


CStucki::~CStucki()
{
}

void CStucki::Diffusion(unsigned char red, unsigned char green,
    unsigned char blue, size_t i, COLORREF color)
{
    if (!m_clrErrors)return;
    auto t = (m_clrErrors[i] + COLOR(RGB(red, green, blue)) - COLOR(color)) / 42.0;
    if (i / m_nWidth & 1)
    {
        if (i%m_nWidth)
            m_clrErrors[i - 1] += t * 8;
        if (i%m_nWidth > 1)
            m_clrErrors[i - 2] += t * 4;
    }
    else
    {
        if (i%m_nWidth != m_nWidth - 1)
            m_clrErrors[i + 1] += t * 8;
        if (i%m_nWidth < m_nWidth - 2)
            m_clrErrors[i + 2] += t * 4;
    }
    if (i < m_nWidth*(m_nHeight - 1))
    {
        if (i%m_nWidth>1)
            m_clrErrors[i + m_nWidth - 2] += t * 2;
        if (i%m_nWidth)
            m_clrErrors[i + m_nWidth - 1] += t * 4;
        m_clrErrors[i + m_nWidth] += t * 8;
        if (i%m_nWidth != m_nWidth - 1)
            m_clrErrors[i + m_nWidth + 1] += t * 4;
        if (i%m_nWidth < m_nWidth - 2)
            m_clrErrors[i + m_nWidth + 2] += t * 2;
    }
    if (i < m_nWidth*(m_nHeight - 2))
    {
        if (i%m_nWidth>1)
            m_clrErrors[i + m_nWidth - 2] += t;
        if (i%m_nWidth)
            m_clrErrors[i + m_nWidth - 1] += t * 2;
        m_clrErrors[i + m_nWidth] += t * 4;
        if (i%m_nWidth != m_nWidth - 1)
            m_clrErrors[i + m_nWidth + 1] += t * 2;
        if (i%m_nWidth < m_nWidth - 2)
            m_clrErrors[i + m_nWidth + 2] += t;
    }
}
