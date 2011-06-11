/*
slowmoVideo creates slow-motion videos from normal-speed videos.
Copyright (C) 2011  Simon A. Eugster (Granjow)  <simon.eu@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
*/

#include "flowField_sV.h"

#include <QDebug>

FlowField_sV::FlowField_sV(int width, int height) :
    m_width(width),
    m_height(height)
{
    m_data = new float[2*m_width*m_height];
}

FlowField_sV::FlowField_sV(int width, int height, float *data, FlowField_sV::GLFormat format) :
    m_width(width),
    m_height(height)
{
    m_data = new float[2*m_width*m_height];

    switch (format) {
    case GLFormat_RGB:
    default:
        float *fieldData = m_data;
        int pos = 0;
        for (int i = 0; i < width*height; i++) {
            *(fieldData++) = data[pos++];
            *(fieldData++) = data[pos++];
            pos++;
        }
    }
}

FlowField_sV::~FlowField_sV()
{
    delete[] m_data;
}

float FlowField_sV::x(int x, int y) const
{
    return m_data[2*(y*m_width+x)+0];
}
float FlowField_sV::y(int x, int y) const
{
    return m_data[2*(y*m_width+x)+1];
}

void FlowField_sV::setX(int x, int y, float value)
{
    m_data[2*(y*m_width+x)+0] = value;
}
void FlowField_sV::setY(int x, int y, float value)
{
    m_data[2*(y*m_width+x)+1] = value;
}

float* FlowField_sV::data()
{
    return m_data;
}

bool FlowField_sV::operator ==(const FlowField_sV& other) const
{

    if (m_width != other.m_width) {
        qDebug() << "Width differs: " << m_width << " vs. " << other.m_width << ".";
        return false;
    }
    if (m_height != other.m_height) {
        qDebug() << "Height differs. " << m_height << " vs. " << other.m_height << "";
        return false;
    }

    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            if (this->x(x,y) != other.x(x,y)) {
                qDebug() << "x Value differs at " << x << "," << y << ": "
                         << this->x(x,y) << "/" << other.x(x,y);
                return false;
            }
            if (this->y(x,y) != other.y(x,y)) {
                qDebug() << "y Value differs at " << x << "," << y << ": "
                         << this->y(x,y) << "/" << other.y(x,y);
                return false;
            }
        }
    }

    return true;
}