<?php
require 'include/app.php';

loadModel('user');

redirectIfNotLogged();
$user = getUser();

// Get orders
$orders = queryDB('SELECT `items`.`name` AS `item_name`, `items`.`price` AS `item_price`, `orders`.`created_at` AS `created_at`, `orders`.`address` AS `address`
                    FROM `orders`
                    INNER JOIN `items` ON `items`.`id` = `orders`.`item_id`
                    WHERE `orders`.`user_id` = ?
                    ORDER BY `orders`.`id` DESC', ['i', $user['id']]);

includeHead();
?>

<h1>
    Bonjour <?= $user['first_name'] ?> !
</h1>

<h3>Vos informations :</h3>

<div>
    <ul>
        <li><b>Prénom :</b> <?= $user['first_name'] ?></li>
        <li><b>Nom :</b> <?= $user['name'] ?></li>
        <li><b>Email :</b> <?= $user['email'] ?></li>
        <li><b>Date d'inscription :</b> <?= $user['created_at'] ?></li>
    </ul>
</div>

<h3>Vos commandes :</h3>

<?php if (empty($orders)): ?>
    <div class="alert alert-error">Vous n'avez encore rien commandé !</div>
<?php else: ?>
    <table>
        <thead>
            <tr>
                <th>Article</th>
                <th>Prix</th>
                <th>Date</th>
                <th>Addresse de livraison</th>
                <th>Actions</th>
            </tr>
        </thead>
        <tbody>
            <?php
            foreach ($orders as $order) {
                echo '<tr>';
                    echo "<td>{$order['item_name']}</td>";
                    echo "<td>{$order['item_price']}</td>";
                    echo "<td>{$order['created_at']}</td>";
                    echo "<td>{$order['address']}</td>";
                    echo "<td><a href=\"order.php\">Télécharger une facture</a></td>";
                echo '</tr>';
            }
            ?>
        </tbody>
    </table>
<?php endif; ?>

<?php
includeFooter()
?>
