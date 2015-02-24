<?php global $base_url; ?>
<div class="zd-broken-list-wrapper">
    <div class="pager">
        <?php print $pager; ?>
    </div>
    <table>
        <tr>
            <th>Link</th>
            <th>Type</th>
            <th>Status</th>
            <th>Operations</th>
        </tr>
        <?php foreach ($organizations as $id =>  $organization): ?>
            <tr>
                <td colspan="4">
                    <b><?php print $organization['name']; ?></b>
                </td>
            </tr>
            <?php foreach ($organization['urls'] as $link): ?>
                <tr>
                    <td>
                        <a href="<?php print $link->url; ?>" target="_blank"><?php print $link->url; ?></a>
                    </td>
                    <td><?php print $link->type; ?></td>
                    <td><?php print $link->status; ?></td>
                    <td>
                        <?php print l(t('Edit'), "{$base_url}/admin/organization-manager/organizations/edit/{$id}", array('query' => drupal_get_destination())); ?>
                    </td>
                </tr>
            <?php endforeach; ?>
        <?php endforeach; ?>
    </table>
    <div class="pager">
        <?php print $pager; ?>
    </div>
</div>