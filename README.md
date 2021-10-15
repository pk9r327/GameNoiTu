# GAME NỐI TỪ

## Dự án bao gồm:
- Project console C++: phần chính của dự án mọi người sẽ làm việc trên đây
- Project lọc dữ liệu viết bằng C# (Này để vào mọi người tham khảo thôi)
- Dữ liệu từ điển tải từ trang: http://informatik.uni-leipzig.de/~duc/Dict/install.html

## Luật code
- Sử dụng class cho các kiểu dữ liệu, tách riêng mỗi class một tệp header (*.h), phần này mình thường tạo sẵn file header các bạn vào xây dựng tiếp thôi
- Các thuộc tính nên để tất cả là private (thoả mãn tính đóng gói OOP). Khi cần đọc hay thay đổi bên ngoài làm thêm phương thức hỗ trợ đọc hoặc thay đổi (get..., set...)
- Các hàm trong GameNoiTu.cpp nên viết dưới hàm main(), sau đó khai báo trong GameNoiTu.h

### Quy tắc đặt tên biến
- Tên class đặt theo PascalCase, ví dụ: UserClass, CategoryClass…
- Tên hằng số thì đặc biệt, viết hoa hết và cách nhau bởi dấu gạch dưới DISCOUNT_PERCENT, LIMIT_RATE…
- Tên hàm và phương thức sử dụng camelCase, ví dụ getUser, getCategory…
- Tên biến cũng sử dụng camelCase, ví dụ loginUser, categoryList…
- Tham số hàm khởi tạo nên thêm hậu tố _ (không chơi `this` nhé c++ cái đó rắc rối ra á), ví dụ
``` C++
class Person
{
public:
    const int DISCOUNT_PERCENT = 92;

    Person(std::string name_, Address address_) 
    {
        name = name_;
        address = address_;
    }

private:
    std::string name;
    Address address;
}

```