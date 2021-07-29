/*
template<typename T, std::uint8_t row, std::uint8_t colomn>;
using ThisType = Matrix<T,row,colomn>;

template<typename T>
std::ostream& operator<<( std::ostream& out, const ThisType& matrix )
{
    for( int row = 0; row < matrix.row; ++row )
    {
        for( int colomn = 0; colomn < matrix.colomn; ++colomn )
            out << matrix.m_data[row][colomn] << ' ';

        out << std::endl;
    }

    return out;
}

template<typename T, std::uint8_t row, std::uint8_t colomn>
ThisType::Matrix( const std::initializer_list<T>& _list )
{
    SetData(_list.data(),_list.size());
}

template<typename T, std::uint8_t row, std::uint8_t colomn>
ThisType::Matrix( const ThisType& other )
{
    SetData(other.m_data,other.length());
}
*/