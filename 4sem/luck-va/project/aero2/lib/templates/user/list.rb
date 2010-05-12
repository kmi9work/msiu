count = 0
"
<table class = 'list'>
" +
if @user and @user[:is_super]
 "
  <caption>
    <a href = 'aero.rb?controller=#{@controller}&action=edit'>Создать новую запись</a>
  </caption>
  "
  else
    ''
  end +
  "
  <thead>
    <tr>
      <th>
        Логин
      </th>
      <th>
        Права
      </th>
      " +
      if @user and @user[:is_super]
       "<th>
          Действия
        </th>"
      else
        ''
      end +
      "
    </tr>
  </thead>
  <tbody>
" + @items.map do |i|
      count += 1
"
    <tr class = 'list#{count % 2}'>
      <td><a href='aero.rb?controller=User&action=show&id=#{i[:id]}'>#{i[:login]}</a></td>
      <td>#{i[:is_super] ? 'Super user' : 'Easy user'}</td>
      "+ 
      if @user and @user[:is_super]
        "
        <td>
          <a href = 'aero.rb?controller=#{@controller}&action=edit&id=#{i[:id]}'>Редактировать</a>
          <a href = 'aero.rb?controller=#{@controller}&action=destroy&id=#{i[:id]}'>Удалить</a>
        </td>
        "
      else
        ''
      end +
      "
    </tr>
"
end.join("\n") + "
  </tbody>
</table>
"