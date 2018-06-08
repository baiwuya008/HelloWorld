#include "flowadapter.h"

FlowAdapter::FlowAdapter(QObject *parent) {
    mCenterPosition = 0;
    mSelectionPosition = 0;
}

FlowAdapter::~FlowAdapter() {

}


void FlowAdapter::setSelection(int position) {
    if (position < 0 || position >= (mList.size() - getMaxCount())) {
        return;
    }

    mSelectionPosition = position;
    computeCenterPosition();
    notifyDataSetChanged();
}


void FlowAdapter::computeCenterPosition() {
    if (mSelectionPosition + getMaxCount() <= mList.size()) {
        this->mCenterPosition = mSelectionPosition + getHalfMaxCount();
    }else if (mSelectionPosition + getMaxCount() > mList.size()) {
        mCenterPosition = (mList.size()-mSelectionPosition)/2 - 1;
    }else {
        mCenterPosition = 0;
    }
}

void FlowAdapter::setInfoList(QList<QString> &list) {
    this->mList = list;
    this->mSelectionPosition = 0;
    computeCenterPosition();
    notifyDataSetChanged();
}


void FlowAdapter::notifyDataSetChanged() {
    emit notifyData();
}

int FlowAdapter::getCenterPosition() {
    return this->mCenterPosition;
}


int FlowAdapter::getLeftPosition() {
    if (mCenterPosition - HALF_MAX_LENGTH >= 0) {
        return mCenterPosition - HALF_MAX_LENGTH;
    }else if (mCenterPosition > 0) {
        return 0;
    }

    return -1;
}

int FlowAdapter::getTotalLength() {
    return mList.size();
}

int FlowAdapter::getMaxCount() {
    return 2*HALF_MAX_LENGTH + 1;
}

int FlowAdapter::getHalfMaxCount() {
    return HALF_MAX_LENGTH;
}

bool FlowAdapter::isLastPosition() {
    if (mList.size() == getCount()) {
        return true;
    }

    return false;
}


int FlowAdapter::getCount() {
    if (mList.size()-(mCenterPosition+1) >= HALF_MAX_LENGTH) {
        return (mCenterPosition+1) + HALF_MAX_LENGTH;
    }else if (mList.size()-(mCenterPosition+1) < HALF_MAX_LENGTH
              && mList.size()-(mCenterPosition+1) > 0) {
        return mList.size();
    }

    return -1;
}


void FlowAdapter::moveNext() {
    movePosition(1);
}
void FlowAdapter::movePrev(){
    movePosition(-1);
}

void FlowAdapter::movePosition(int position) {
    mCenterPosition += position;
    mCenterPosition = mCenterPosition < 0 ? 0 : mCenterPosition;
    mCenterPosition = mCenterPosition > (mList.size()-1) ? (mList.size()-1) : mCenterPosition;
}

QString FlowAdapter::getPath(int position) {
    return mList.at(position);
}
