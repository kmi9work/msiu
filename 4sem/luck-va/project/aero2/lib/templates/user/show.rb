"
<table class = 'list'>
  <tbody>
    <tr>
      <th>
        Логин:
      </th>
      <th>
        #{@item[:login]}
      </th>  
    </tr>
    <tr>
      <th>
        Информация:
      </th>
      <th>  
        #{@item[:info]}
      </th>
    </tr>
    <tr>
      <th>
        Права:
      </th>
      <th>  
        #{@item[:is_super] ? 'Super user' : 'Easy user'}
      </th>
    </tr>
    " + 
    if @user and @user[:is_super]
    "
    <tr>
      <th>
        Действия:
      </th>
      <th>  
        <a href = 'aero.rb?controller=User&action=destroy&id=#{@item[:id]}'>Удалить</a> | 
        <a href = 'aero.rb?controller=User&action=edit&id=#{@item[:id]}'>Редактировать</a>
      </th>
    </tr>
    "
    else
      ''
    end + "
  </tbody>
</table>
"
