"
<form name = 'aero' action = 'aero.rb' method = 'post'>
<input type = 'hidden' name = 'controller' value = 'User'>
<input type = 'hidden' name = 'action' value = 'register'>
<input type = 'hidden' name = 'is_commit' value = 'true'>
<table class = 'list'>
  <caption>
    #{@header}<br>
    <span style = 'color: Red;'>#{@message}</span>
  </caption>
  <thead>
  <tbody>
    <tr>
      <th>Логин:</th>
      <td><input type = 'text' name = 'item[login]' value = ''></td>
    </tr>
    <tr>
      <th>Пароль:</th>
      <td><input type = 'password' name = 'item[password1]' value = ''></td>
    </tr>
    <tr>
      <th>Повторите пароль:</th>
      <td><input type = 'password' name = 'item[password2]' value = ''></td>
    </tr>
    <tr>
      <th>Информация:</th>
      <td><input type = 'text' name = 'item[info]' value = ''></td>
    </tr>
    <tr>
      <th>Суперпользователь?</th>
      <td>
        <select name='item[is_super]'>
          <option value = '1'>Да</option>
          <option value = '0' selected>Нет</option>
        </select>
      </td>
    </tr>
  </tbody>
  <tfoot>
    <tr>
      <th colspan = '2'>
        <input type = 'submit' value = 'Внести изменения'>
        <input type = 'button' value = 'Назад к списку'
               onclick = 'javascript:document.location=\"aero.rb?controller=User&action=list\"'>
      </th>
    </tr>
  </tfoot>
</table>
"
