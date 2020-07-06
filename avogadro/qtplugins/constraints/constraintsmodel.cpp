#include "constraintsmodel.h"
#include <QtCore/QMutexLocker>
#include <QtCore/QDebug>
#include <QString>


using namespace std;

namespace Avogadro
{
  namespace QtPlugins{

    void ConstraintsModel::emitDataChanged()
    {
      emit dataChanged(QModelIndex(), QModelIndex());
    }
    
    int ConstraintsModel::rowCount(const QModelIndex &) const
    {
      return ConstraintsList.size();
    }

    int ConstraintsModel::columnCount(const QModelIndex &) const
    {
      return 6;
    }

    QVariant ConstraintsModel::data(const QModelIndex &index, int role) const
    {
      if (!index.isValid())
        return QVariant();

      if (index.row() >= ConstraintsList.size())
        return QVariant();

      if (role == Qt::DisplayRole)
        switch (index.column()) {
        case 0:
          if (ConstraintsList[index.row()].GetConstraintType() == 0)
            return QString("Ignore Atom");
          else if (ConstraintsList[index.row()].GetConstraintType() == 1)
            return QString("Fix Atom");
          else if (ConstraintsList[index.row()].GetConstraintType() == 2)
            return QString("Fix Atom X");
          else if (ConstraintsList[index.row()].GetConstraintType() == 3)
            return QString("Fix Atom Y");
          else if (ConstraintsList[index.row()].GetConstraintType() == 4)
            return QString("Fix Atom Z");
          else if (ConstraintsList[index.row()].GetConstraintType() == 5)
            return QString("Distance");
          else if (ConstraintsList[index.row()].GetConstraintType() == 6)
            return QString("Angle");
          else if (ConstraintsList[index.row()].GetConstraintType() == 7)
            return QString("Torsion angle");
          break;
        case 1:
          return ConstraintsList[index.row()].GetConstraintValue();
          break;
        case 2:
          if (ConstraintsList[index.row()].GetConstraintAtomA())
            {
              QVariant v;
              v.setValue(static_cast<int>(ConstraintsList[index.row()].GetConstraintAtomA()));
              return v;
            }
          else
            {
              return "NA";
            }
          break;
        case 3:
          if (ConstraintsList[index.row()].GetConstraintAtomB())
            {
              QVariant v;
              v.setValue(static_cast<int>(ConstraintsList[index.row()].GetConstraintAtomB()));
              return v;
            }
          else
            {
              return "NA";
            }
          break;
        case 4:
          if (ConstraintsList[index.row()].GetConstraintAtomC())
            {
              QVariant v;
              v.setValue(static_cast<int>(ConstraintsList[index.row()].GetConstraintAtomC()));
              return v;
            }
          else
            {
              return "NA";
                }
          break;
        case 5:
          if (ConstraintsList[index.row()].GetConstraintAtomD())
            {
              QVariant v;
              v.setValue(static_cast<int>(ConstraintsList[index.row()].GetConstraintAtomD()));
              return v;
            }
          else
            {
              return "NA";
                }
          break;
        }

      return QVariant();
    }
  
    QVariant ConstraintsModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
      if (role != Qt::DisplayRole)
        return QVariant();

      if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
          return QString("Type");
          break;
        case 1:
          return QString("Value");
          break;
        case 2:
          return QString("Atom idx 1");
          break;
        case 3:
          return QString("Atom idx 2");
          break;
        case 4:
          return QString("Atom idx 3");
          break;
        case 5:
          return QString("Atom idx 4");
          break;
        }
      }
    
      return QString("Constraint %1").arg(section + 1);
    }

    void ConstraintsModel::addConstraint(int type, int a, int b, int c, int d, double value)
    {
      beginInsertRows(QModelIndex(), ConstraintsList.size(), ConstraintsList.size());
      ConstraintsList << Constraint(type, a, b, c, d, value, this);
      endInsertRows();
    }
 
    void ConstraintsModel::clear()
    {
      qDebug() << "ConstraintsModel::clear()" << endl;
      if (ConstraintsList.size()) {
        beginRemoveRows(QModelIndex(), 0, ConstraintsList.size() - 1); 
        ConstraintsList.clear();
        endRemoveRows();
      }
    }
  
    void ConstraintsModel::deleteConstraint(int index)
    { 
      qDebug() << "ConstraintsModel::deleteConstraint(" << index << ")" << endl;
      if (ConstraintsList.size() && (index >= 0)) {
        beginRemoveRows(QModelIndex(), index, index); 
        ConstraintsList.removeAt(index);
        endRemoveRows();
      }
    }

    QJsonObject ConstraintsModel::toJson()
    {
      QJsonObject ConstraintsMJ;
      ConstraintsMJ["total"] = ConstraintsList.size();

      if(ConstraintsList.size())
        {
        for(int i = 0; i < ConstraintsList.size(); i++)
          {
            ConstraintsMJ.insert(QString::number(i), ConstraintsList[i].toJson());
          }
        }

      return ConstraintsMJ;
    }
  }
} // end namespace Avogadro
