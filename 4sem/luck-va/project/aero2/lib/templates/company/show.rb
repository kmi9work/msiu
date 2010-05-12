"
<table class = 'list'>
  <tbody>
    <tr>
      <th>
        Название компании:
      </th>
      <th>
        #{@item[:name]}
      </th>  
    </tr>
    <tr>
      <th>
        Код компании:
      </th>
      <th>  
        #{@item[:code]}
      </th>
    </tr>
    <tr>
      <th>
        Описание компании:
      </th>
      <th>  
        #{@item[:description]}
      </th>
    </tr>
    " +
    if @user and !@user[:is_super]
    "
    <tr>
      <th>
        Действия:
      </th>
      <th>  
        <a href = 'aero.rb?controller=Company&action=destroy&id=#{@item[:id]}'>Удалить</a> | 
        <a href = 'aero.rb?controller=Company&action=edit&id=#{@item[:id]}'>Редактировать</a>
      </th>
    </tr>
    "
    else
      ''
    end + 
    "
  </tbody>
</table>
"